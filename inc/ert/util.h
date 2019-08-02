#pragma once

#ifdef __cplusplus
extern "C" {
#endif

uint32_t Util_FastRound(uint32_t x, int bpnt);

#define UTIL_CRC_POLY				0x8408
#define UTIL_CRC_BAD				0xFFFF

uint16_t Util_Crc16(void* data_p, uint16_t length);

#ifdef __cplusplus
}
#endif