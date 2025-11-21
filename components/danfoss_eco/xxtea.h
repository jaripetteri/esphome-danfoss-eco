#pragma once
#include "xxtea_c.h"   // tämä on vendoroitu kirjaston header

#define XXTEA_STATUS_NOT_INITIALIZED -1
#define XXTEA_STATUS_SUCCESS 0
#define XXTEA_STATUS_GENERAL_ERROR 1
#define XXTEA_STATUS_PARAMETER_ERROR 2
#define XXTEA_STATUS_SIZE_ERROR 3

class Xxtea {
public:
    Xxtea() : status_(XXTEA_STATUS_NOT_INITIALIZED) {}

    int set_key(uint8_t *key, size_t len);

    int encrypt(uint8_t *data, size_t len, uint8_t *buf, size_t *outlen);
    int decrypt(uint8_t *data, size_t len, uint8_t *buf, size_t *outlen);

    int status() const { return status_; }

private:
    int status_;
    uint8_t key_[16];   // XXTEA avain binäärimuodossa
    size_t key_len_;
};
