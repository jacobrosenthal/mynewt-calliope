//
// Created by Alfred Schilken on 25.08.17.
//

#include "eddystone_util.h"
#include "host/ble_hs.h"

int
cmd_parse_eddystone_url(char *full_url, uint8_t *out_scheme, char *out_body,
                        uint8_t *out_body_len, uint8_t *out_suffix)
{
    static const struct {
        char *s;
        uint8_t scheme;
    } schemes[] = {
            { "http://www.", BLE_EDDYSTONE_URL_SCHEME_HTTP_WWW },
            { "https://www.", BLE_EDDYSTONE_URL_SCHEME_HTTPS_WWW },
            { "http://", BLE_EDDYSTONE_URL_SCHEME_HTTP },
            { "https://", BLE_EDDYSTONE_URL_SCHEME_HTTPS },
    };

    static const struct {
        char *s;
        uint8_t code;
    } suffixes[] = {
            { ".com/", BLE_EDDYSTONE_URL_SUFFIX_COM_SLASH },
            { ".org/", BLE_EDDYSTONE_URL_SUFFIX_ORG_SLASH },
            { ".edu/", BLE_EDDYSTONE_URL_SUFFIX_EDU_SLASH },
            { ".net/", BLE_EDDYSTONE_URL_SUFFIX_NET_SLASH },
            { ".info/", BLE_EDDYSTONE_URL_SUFFIX_INFO_SLASH },
            { ".biz/", BLE_EDDYSTONE_URL_SUFFIX_BIZ_SLASH },
            { ".gov/", BLE_EDDYSTONE_URL_SUFFIX_GOV_SLASH },
            { ".com", BLE_EDDYSTONE_URL_SUFFIX_COM },
            { ".org", BLE_EDDYSTONE_URL_SUFFIX_ORG },
            { ".edu", BLE_EDDYSTONE_URL_SUFFIX_EDU },
            { ".net", BLE_EDDYSTONE_URL_SUFFIX_NET },
            { ".info", BLE_EDDYSTONE_URL_SUFFIX_INFO },
            { ".biz", BLE_EDDYSTONE_URL_SUFFIX_BIZ },
            { ".gov", BLE_EDDYSTONE_URL_SUFFIX_GOV },
    };

    char *prefix;
    char *suffix;
    int full_url_len;
    int prefix_len;
    int suffix_len;
    int suffix_idx;
    int rc;
    int i;

    full_url_len = strlen(full_url);

    rc = BLE_HS_EINVAL;
    for (i = 0; i < sizeof schemes / sizeof schemes[0]; i++) {
        prefix = schemes[i].s;
        prefix_len = strlen(schemes[i].s);

        if (full_url_len >= prefix_len &&
            memcmp(full_url, prefix, prefix_len) == 0) {

            *out_scheme = i;
            rc = 0;
            break;
        }
    }
    if (rc != 0) {
        return rc;
    }

    rc = BLE_HS_EINVAL;
    for (i = 0; i < sizeof suffixes / sizeof suffixes[0]; i++) {
        suffix = suffixes[i].s;
        suffix_len = strlen(suffixes[i].s);

        suffix_idx = full_url_len - suffix_len;
        if (suffix_idx >= prefix_len &&
            memcmp(full_url + suffix_idx, suffix, suffix_len) == 0) {

            *out_suffix = i;
            rc = 0;
            break;
        }
    }
    if (rc != 0) {
        *out_suffix = BLE_EDDYSTONE_URL_SUFFIX_NONE;
        *out_body_len = full_url_len - prefix_len;
    } else {
        *out_body_len = full_url_len - prefix_len - suffix_len;
    }

    memcpy(out_body, full_url + prefix_len, *out_body_len);

    return 0;
}