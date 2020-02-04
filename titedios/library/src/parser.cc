#include "parser.h"

MDATA mdata;

inline std::string rtrim (std::string s, const std::string& drop = " ")
{
    return s.erase(s.find_last_not_of(drop)+1);
}   

std::vector<std::pair<std::string, std::string>> parser (std::string message)
{
    int result = -1;
    /// tokenizing
    std::vector<std::string> temp_field; 
    std::vector<std::pair<std::string, std::string>> list_of_field;

    boost::split(temp_field, message, boost::is_any_of("\n")); 

    /// remove END
    temp_field.pop_back();

	for (auto const & i: temp_field) {
        //boost::algorithm::trim_right_copy_if(i, boost::is_any_of("\r"));
        rtrim(i, "\r");

        std::vector<std::string> tmp;
        boost::split(tmp, i, boost::is_any_of(":"));

        int mdata_states = MDATA_STATES_INIT;
        if (0 == strcmp(tmp[0].c_str(), "MDATA")) {
            std::cout << COUT_PREFIX << "decoding MDATA\n";
            /* get information from MDATA */
            /// State machine design
            /// 1. header
            /// 2. sub-header
            /// 3. main
            /// 4. end
            /// working 1 -> 2 -> 3 -> 4 -> 1
            mdata_states = MDATA_STATES_HEADER;
            /// step 1. header
            result = extractMDATA(&mdata_states, message);
            if (0 != result) {
                /* Error */
            }

            std::cout << COUT_PREFIX << "========== check values ==========" << std::endl;
            std::cout << COUT_PREFIX << "mime version: " << mdata.mime_version << std::endl;
            std::cout << COUT_PREFIX << "type: " << mdata.type << std::endl;
            std::cout << COUT_PREFIX << "charset: " << mdata.charset << std::endl;
            std::cout << COUT_PREFIX << "encoding: " << mdata.encoding << std::endl;
            std::cout << COUT_PREFIX << "message_body: " << mdata.message_body << std::endl;

        } else {
            // remove abnormal data
            if (2 != tmp.size())
                continue;

            list_of_field.push_back(std::make_pair(tmp[0], tmp[1]));
        }
    }

    return list_of_field;
}

int extractMDATA(int *state, std::string raw_message)
{
    int n = raw_message.length();
    char message_array[n + 1];
    strcpy(message_array, raw_message.c_str());

    char *start_point;
    char *end_point;
    start_point = message_array;
    for (int k = 0; 4 > k; ++k) {
        start_point = strstr (start_point, "MDATA");
        end_point = strstr (start_point, "\r\nMDATA:\r\n");

        char *end_to_extract;
        unsigned char *decoded_msg;
        int extracted_length = 0;
        int base64_result = 0;
        char msg_buf[4096];
        std::string raw_data;
        switch (*state) {
            case MDATA_STATES_INIT:
            break;
            case MDATA_STATES_HEADER:
                std::cout << COUT_PREFIX << "HEADER\n";

                start_point += 6;

                while (end_point >= start_point) {
                    // find end point to extract raw data
                    end_to_extract = strstr(start_point, "\r\nMDATA:");
                    // get length
                    extracted_length = (end_to_extract - start_point) / sizeof(char);
                    // copy to temporate buffer
                    memset(msg_buf, 0x00, sizeof (msg_buf));
                    strncpy(msg_buf, start_point, extracted_length);

                    char extracted_sub_field[100];
                    char *start_in_buf;
                    char *end_in_buf;
                    if (0 == strncmp("MIME-Version", msg_buf, 12)) {
                        /* MIME version */
                        start_in_buf = strstr(msg_buf, "MIME-Version");

                        memset(extracted_sub_field, 0x00, sizeof(extracted_sub_field));
                        strncpy(extracted_sub_field, start_in_buf + 13, (&msg_buf[strlen(msg_buf)] - (start_in_buf + 13))/sizeof(char));

                        memcpy(mdata.mime_version, extracted_sub_field, strlen(extracted_sub_field)); // if strlen were over the type size ???
                    }
                    // moving start point at next searched sector
                    start_point = end_to_extract + 8;
                }

                *state = MDATA_STATES_SUB_HEADER;
            break;
            case MDATA_STATES_SUB_HEADER:
                std::cout << COUT_PREFIX << "SUB HEADER\n";
                start_point += 6;

                while (end_point >= start_point) {
                    // find end point to extract raw data
                    end_to_extract = strstr(start_point, "\r\nMDATA:");
                    // get length
                    extracted_length = (end_to_extract - start_point) / sizeof(char);
                    // copy to temporate buffer
                    memset(msg_buf, 0x00, sizeof (msg_buf));
                    strncpy(msg_buf, start_point, extracted_length);

                    char extracted_sub_field[100];
                    char *start_in_buf;
                    char *end_in_buf;
                    if (0 == strncmp("Content-Type", msg_buf, 12)) {
                        /* content type */
                        start_in_buf = strstr(msg_buf, "Content-Type");
                        end_in_buf = strstr(start_in_buf, ";");

                        memset(extracted_sub_field, 0x00, sizeof(extracted_sub_field));
                        strncpy(extracted_sub_field, start_in_buf + 13, (end_in_buf - (start_in_buf + 13))/sizeof(char));

                        memcpy(mdata.type, extracted_sub_field, strlen(extracted_sub_field)); // if strlen were over the type size ???

                        /* charset */
                        start_in_buf = end_in_buf + 1;
                        start_in_buf = strstr(start_in_buf, "charset");

                        memset(extracted_sub_field, 0x00, sizeof(extracted_sub_field));
                        strncpy(extracted_sub_field, start_in_buf + 9, (&msg_buf[strlen(msg_buf)-1] - (start_in_buf + 9))/sizeof(char));

                        memcpy(mdata.charset, extracted_sub_field, strlen(extracted_sub_field)); // if strlen were over the type size ???
                    } else if (0 == strncmp("Content-Transfer-Encoding", msg_buf, 25)) {
                        /* encoding */
                        start_in_buf = strstr(msg_buf, "Content-Transfer-Encoding");

                        memset(extracted_sub_field, 0x00, sizeof(extracted_sub_field));
                        strncpy(extracted_sub_field, start_in_buf + 26, (&msg_buf[strlen(msg_buf)] - (start_in_buf + 26))/sizeof(char));

                        memcpy(mdata.encoding, extracted_sub_field, strlen(extracted_sub_field)); // if strlen were over the type size ???
                    }
                    
                    // moving start point at next searched sector
                    start_point = end_to_extract + 8;
                } 

                *state = MDATA_STATES_MAIN;
            break;
            case MDATA_STATES_MAIN:
                std::cout << COUT_PREFIX << "MAIN\n";
                /* Extract raw data */
                start_point += 6;
                while (end_point >= start_point) {
                    // find end point to extract raw data
                    end_to_extract = strstr(start_point, "\r\nMDATA:");
                    // get length
                    extracted_length = (end_to_extract - start_point) / sizeof(char);
                    // copy to temporate buffer
                    memset(msg_buf, 0x00, sizeof (msg_buf));
                    strncpy(msg_buf, start_point, extracted_length);
                    // append raw data
                    raw_data += msg_buf;
                    // moving start point at next searched sector
                    start_point = end_to_extract + 8;
                } 
                /* converting base64(raw data) to string */
                decoded_msg = __base64_decode ((const unsigned char *)raw_data.c_str(), raw_data.length(), &base64_result);
                memcpy(mdata.message_body, decoded_msg, sizeof(mdata.message_body));

                /* End the state */
                *state = MDATA_STATES_END;
            break;
            case MDATA_STATES_END:
                std::cout << COUT_PREFIX << "END\n";
                // MDATA:------=_NextPart_000_0049_01C851E9.827BA430
                // MDATA:
                start_point += 6;

                *state = MDATA_STATES_HEADER;
            break;
            default:
                *state = MDATA_STATES_INIT;
            break;
        }

        /// 
        start_point = end_point + 7;
    } // for ()

    std::cout << COUT_PREFIX << "return: " << *state << std::endl;

    return 0;
}