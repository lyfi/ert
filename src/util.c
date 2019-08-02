#include <stdint.h>

#include <ert/util.h>


/** 快速定点数四舍五入函数
 * @param[in] x 定点数
 * @param[in] bpnt 小数位数
 *
 */
uint32_t 
Util_FastRound(uint32_t x, int bpnt) {
	//http://lithetechnology.com/a-fast-rounding-method-for-fixed-point-numbers/
	uint32_t tmp = 1;
	tmp <<= (bpnt - 1);
	x += tmp;
	tmp = -1;
	tmp <<= bpnt;
	return (x & tmp);
}


/*
//                                      16   12   5
// this is the CCITT CRC 16 polynomial X  + X  + X  + 1.
// This works out to be 0x1021, but the way the algorithm works
// lets us use 0x8408 (the reverse of the bit pattern).  The high
// bit is always assumed to be set, thus we only use 16 bits to
// represent the 17 bit value.
*/
uint16_t
Util_Crc16(void* data_p, uint16_t length) {

	uint8_t* buf = (uint8_t*)data_p;
	uint8_t i;
	uint32_t data;
	uint32_t crc = 0xffff;

	if (length == 0) {
		return (~crc);
	}

	do {
		for (i = 0, data = (unsigned int)0xff & *buf++; i < 8; i++, data >>= 1) {
			if ((crc & 0x0001) ^ (data & 0x0001)) {
				crc = (crc >> 1) ^ UTIL_CRC_POLY;
			}
			else {
				crc >>= 1;
			}
		}
	} while (--length);

	crc = ~crc;
	data = crc;
	crc = (crc << 8) | (data >> 8 & 0xff);

	return (uint16_t)crc;
}