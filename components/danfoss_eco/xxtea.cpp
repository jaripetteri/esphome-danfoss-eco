#include "xxtea.h"
// xxtea-iot-crypt provides xxtea_encrypt/xxtea_decrypt

int Xxtea::set_key(uint8_t *key, size_t len)
{
    this->status_ = XXTEA_STATUS_GENERAL_ERROR;
    if (key == nullptr || len == 0 || len > MAX_XXTEA_KEY8) {
        this->status_ = XXTEA_STATUS_PARAMETER_ERROR;
        return this->status_;
    }
    memset(this->xxtea_key, 0, MAX_XXTEA_KEY8);
    memcpy(this->xxtea_key, key, len);
    this->status_ = XXTEA_STATUS_SUCCESS;
    return this->status_;
}

int Xxtea::encrypt(uint8_t *data, size_t len, uint8_t *buf, size_t *maxlen) {
    xxtea_long out_len;
    void *out = xxtea_encrypt(data, (xxtea_long)len, this->xxtea_key, MAX_XXTEA_KEY8, &out_len);
    if (!out) return XXTEA_STATUS_GENERAL_ERROR;
    if (*maxlen < (size_t)out_len) {
        free(out);
        return XXTEA_STATUS_SIZE_ERROR;
    }
    memcpy(buf, out, out_len);
    *maxlen = out_len;
    free(out);
    return XXTEA_STATUS_SUCCESS;
}

int Xxtea::decrypt(uint8_t *data, size_t len, uint8_t *buf, size_t *outlen) {
    xxtea_long out_len;
    void *out = xxtea_decrypt(data, (xxtea_long)len, this->xxtea_key, MAX_XXTEA_KEY8, &out_len);
    if (!out) return XXTEA_STATUS_GENERAL_ERROR;
    memcpy(buf, out, out_len);
    *outlen = out_len;
    free(out);
    return XXTEA_STATUS_SUCCESS;
}