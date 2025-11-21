#include "xxtea.h"
#include <cstring>
#include <cstdlib>

int Xxtea::set_key(uint8_t *key, size_t len) {
    if (!key || len == 0 || len > sizeof(key_)) {
        status_ = XXTEA_STATUS_PARAMETER_ERROR;
        return status_;
    }
    memset(key_, 0, sizeof(key_));
    memcpy(key_, key, len);
    key_len_ = len;
    status_ = XXTEA_STATUS_SUCCESS;
    return status_;
}

int Xxtea::encrypt(uint8_t *data, size_t len, uint8_t *buf, size_t *outlen) {
    xxtea_long out_len;
    void *out = xxtea_encrypt(data, (xxtea_long)len, key_, (xxtea_long)key_len_, &out_len);
    if (!out) {
        return XXTEA_STATUS_GENERAL_ERROR;
    }
    if (*outlen < (size_t)out_len) {
        free(out);
        return XXTEA_STATUS_SIZE_ERROR;
    }
    memcpy(buf, out, out_len);
    *outlen = out_len;
    free(out);
    return XXTEA_STATUS_SUCCESS;
}

int Xxtea::decrypt(uint8_t *data, size_t len, uint8_t *buf, size_t *outlen) {
    xxtea_long out_len;
    void *out = xxtea_decrypt(data, (xxtea_long)len, key_, (xxtea_long)key_len_, &out_len);
    if (!out) {
        return XXTEA_STATUS_GENERAL_ERROR;
    }
    if (*outlen < (size_t)out_len) {
        free(out);
        return XXTEA_STATUS_SIZE_ERROR;
    }
    memcpy(buf, out, out_len);
    *outlen = out_len;
    free(out);
    return XXTEA_STATUS_SUCCESS;
}
