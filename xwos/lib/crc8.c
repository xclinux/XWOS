/**
 * @file
 * @brief XWOS通用库：CRC8
 * @author
 * + 隐星魂 (Roy.Sun) <https://xwos.tech>
 * @copyright
 * + (c) 2015 隐星魂 (Roy.Sun) <https://xwos.tech>
 * > This Source Code Form is subject to the terms of the Mozilla Public
 * > License, v. 2.0. If a copy of the MPL was not distributed with this
 * > file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      include      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#include <xwos/standard.h>
#include <xwos/lib/xwbop.h>
#include <xwos/lib/crc8.h>

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       macros      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       .data       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#if defined(XWLIBCFG_CRC8_0X07) && (1 == XWLIBCFG_CRC8_0X07)
/**
 * @brief 多项式0x7的查询表
 */
__xwlib_rodata const xwu8_t xwlib_crc8tbl_0x07[256] = {
        0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15,
        0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
        0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65,
        0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
        0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5,
        0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
        0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85,
        0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
        0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2,
        0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
        0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2,
        0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
        0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32,
        0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
        0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42,
        0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
        0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C,
        0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
        0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC,
        0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
        0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C,
        0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
        0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C,
        0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
        0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B,
        0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
        0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B,
        0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
        0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB,
        0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
        0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB,
        0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3,
};
#endif /* XWLIBCFG_CRC8_0X07 */

#if defined(XWLIBCFG_CRC8_0X31) && (1 == XWLIBCFG_CRC8_0X31)
/**
 * @brief 多项式0x31的查询表
 */
__xwlib_rodata const xwu8_t xwlib_crc8tbl_0x31[256] = {
        0x00, 0x31, 0x62, 0x53, 0xC4, 0xF5, 0xA6, 0x97,
        0xB9, 0x88, 0xDB, 0xEA, 0x7D, 0x4C, 0x1F, 0x2E,
        0x43, 0x72, 0x21, 0x10, 0x87, 0xB6, 0xE5, 0xD4,
        0xFA, 0xCB, 0x98, 0xA9, 0x3E, 0x0F, 0x5C, 0x6D,
        0x86, 0xB7, 0xE4, 0xD5, 0x42, 0x73, 0x20, 0x11,
        0x3F, 0x0E, 0x5D, 0x6C, 0xFB, 0xCA, 0x99, 0xA8,
        0xC5, 0xF4, 0xA7, 0x96, 0x01, 0x30, 0x63, 0x52,
        0x7C, 0x4D, 0x1E, 0x2F, 0xB8, 0x89, 0xDA, 0xEB,
        0x3D, 0x0C, 0x5F, 0x6E, 0xF9, 0xC8, 0x9B, 0xAA,
        0x84, 0xB5, 0xE6, 0xD7, 0x40, 0x71, 0x22, 0x13,
        0x7E, 0x4F, 0x1C, 0x2D, 0xBA, 0x8B, 0xD8, 0xE9,
        0xC7, 0xF6, 0xA5, 0x94, 0x03, 0x32, 0x61, 0x50,
        0xBB, 0x8A, 0xD9, 0xE8, 0x7F, 0x4E, 0x1D, 0x2C,
        0x02, 0x33, 0x60, 0x51, 0xC6, 0xF7, 0xA4, 0x95,
        0xF8, 0xC9, 0x9A, 0xAB, 0x3C, 0x0D, 0x5E, 0x6F,
        0x41, 0x70, 0x23, 0x12, 0x85, 0xB4, 0xE7, 0xD6,
        0x7A, 0x4B, 0x18, 0x29, 0xBE, 0x8F, 0xDC, 0xED,
        0xC3, 0xF2, 0xA1, 0x90, 0x07, 0x36, 0x65, 0x54,
        0x39, 0x08, 0x5B, 0x6A, 0xFD, 0xCC, 0x9F, 0xAE,
        0x80, 0xB1, 0xE2, 0xD3, 0x44, 0x75, 0x26, 0x17,
        0xFC, 0xCD, 0x9E, 0xAF, 0x38, 0x09, 0x5A, 0x6B,
        0x45, 0x74, 0x27, 0x16, 0x81, 0xB0, 0xE3, 0xD2,
        0xBF, 0x8E, 0xDD, 0xEC, 0x7B, 0x4A, 0x19, 0x28,
        0x06, 0x37, 0x64, 0x55, 0xC2, 0xF3, 0xA0, 0x91,
        0x47, 0x76, 0x25, 0x14, 0x83, 0xB2, 0xE1, 0xD0,
        0xFE, 0xCF, 0x9C, 0xAD, 0x3A, 0x0B, 0x58, 0x69,
        0x04, 0x35, 0x66, 0x57, 0xC0, 0xF1, 0xA2, 0x93,
        0xBD, 0x8C, 0xDF, 0xEE, 0x79, 0x48, 0x1B, 0x2A,
        0xC1, 0xF0, 0xA3, 0x92, 0x05, 0x34, 0x67, 0x56,
        0x78, 0x49, 0x1A, 0x2B, 0xBC, 0x8D, 0xDE, 0xEF,
        0x82, 0xB3, 0xE0, 0xD1, 0x46, 0x77, 0x24, 0x15,
        0x3B, 0x0A, 0x59, 0x68, 0xFF, 0xCE, 0x9D, 0xAC,
};
#endif /* XWLIBCFG_CRC8_0X31 */

#if defined(XWLIBCFG_CRC8_0X9B) && (1 == XWLIBCFG_CRC8_0X9B)
/**
 * @brief 多项式0x31的查询表
 */
__xwlib_rodata const xwu8_t xwlib_crc8tbl_0x9B[256] = {
        0x00, 0x9B, 0xAD, 0x36, 0xC1, 0x5A, 0x6C, 0xF7,
        0x19, 0x82, 0xB4, 0x2F, 0xD8, 0x43, 0x75, 0xEE,
        0x32, 0xA9, 0x9F, 0x04, 0xF3, 0x68, 0x5E, 0xC5,
        0x2B, 0xB0, 0x86, 0x1D, 0xEA, 0x71, 0x47, 0xDC,
        0x64, 0xFF, 0xC9, 0x52, 0xA5, 0x3E, 0x08, 0x93,
        0x7D, 0xE6, 0xD0, 0x4B, 0xBC, 0x27, 0x11, 0x8A,
        0x56, 0xCD, 0xFB, 0x60, 0x97, 0x0C, 0x3A, 0xA1,
        0x4F, 0xD4, 0xE2, 0x79, 0x8E, 0x15, 0x23, 0xB8,
        0xC8, 0x53, 0x65, 0xFE, 0x09, 0x92, 0xA4, 0x3F,
        0xD1, 0x4A, 0x7C, 0xE7, 0x10, 0x8B, 0xBD, 0x26,
        0xFA, 0x61, 0x57, 0xCC, 0x3B, 0xA0, 0x96, 0x0D,
        0xE3, 0x78, 0x4E, 0xD5, 0x22, 0xB9, 0x8F, 0x14,
        0xAC, 0x37, 0x01, 0x9A, 0x6D, 0xF6, 0xC0, 0x5B,
        0xB5, 0x2E, 0x18, 0x83, 0x74, 0xEF, 0xD9, 0x42,
        0x9E, 0x05, 0x33, 0xA8, 0x5F, 0xC4, 0xF2, 0x69,
        0x87, 0x1C, 0x2A, 0xB1, 0x46, 0xDD, 0xEB, 0x70,
        0x0B, 0x90, 0xA6, 0x3D, 0xCA, 0x51, 0x67, 0xFC,
        0x12, 0x89, 0xBF, 0x24, 0xD3, 0x48, 0x7E, 0xE5,
        0x39, 0xA2, 0x94, 0x0F, 0xF8, 0x63, 0x55, 0xCE,
        0x20, 0xBB, 0x8D, 0x16, 0xE1, 0x7A, 0x4C, 0xD7,
        0x6F, 0xF4, 0xC2, 0x59, 0xAE, 0x35, 0x03, 0x98,
        0x76, 0xED, 0xDB, 0x40, 0xB7, 0x2C, 0x1A, 0x81,
        0x5D, 0xC6, 0xF0, 0x6B, 0x9C, 0x07, 0x31, 0xAA,
        0x44, 0xDF, 0xE9, 0x72, 0x85, 0x1E, 0x28, 0xB3,
        0xC3, 0x58, 0x6E, 0xF5, 0x02, 0x99, 0xAF, 0x34,
        0xDA, 0x41, 0x77, 0xEC, 0x1B, 0x80, 0xB6, 0x2D,
        0xF1, 0x6A, 0x5C, 0xC7, 0x30, 0xAB, 0x9D, 0x06,
        0xE8, 0x73, 0x45, 0xDE, 0x29, 0xB2, 0x84, 0x1F,
        0xA7, 0x3C, 0x0A, 0x91, 0x66, 0xFD, 0xCB, 0x50,
        0xBE, 0x25, 0x13, 0x88, 0x7F, 0xE4, 0xD2, 0x49,
        0x95, 0x0E, 0x38, 0xA3, 0x54, 0xCF, 0xF9, 0x62,
        0x8C, 0x17, 0x21, 0xBA, 0x4D, 0xD6, 0xE0, 0x7B,
};
#endif /* XWLIBCFG_CRC8_0X31 */

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********         function prototypes         ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#if defined(SOCCFG_CRC8) && (1 == SOCCFG_CRC8)
extern
xwer_t soc_crc8_cal(xwu8_t * crc8,
                    bool refin, xwu8_t polynomial,
                    const xwu8_t stream[], xwsz_t * size);
#else /* SOCCFG_CRC8 */
#define soc_crc8_cal(crc8, refin, plynml, stream, size)         (-EOPNOTSUPP)
#endif /* !SOCCFG_CRC8 */

static __xwlib_code
xwer_t xwlib_crc8_swcal(xwu8_t * crc8,
                        bool refin, xwu8_t plynml,
                        const xwu8_t stream[], xwsz_t * size);

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********      function implementations       ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
/**
 * @brief 软件方式计算一段数据的CRC8校验值
 * @param crc8: 指向缓冲区的指针，此缓冲区：
 *              (I) 作为输入，表示初始值
 *              (O) 作为输出，返回计算结果
 * @param refin: (I) 是否按位镜像翻转输入的每个字节(xwbop_rbit8)
 * @param plynml: (I) 多项式
 * @param stream: (I) 指向数据的指针
 * @param size: 指向缓冲区的指针，此缓冲区：
 *              (I) 作为输入，表示数据长度
 *              (O) 作为输出，返回剩余未计算的数据长度
 * @return 错误码
 * @retval XWOK: 没有错误，计算结果有效
 * @retval -EOPNOTSUPP: 不支持的多项式
 */
static __xwlib_code
xwer_t xwlib_crc8_swcal(xwu8_t * crc8,
                        bool refin, xwu8_t plynml,
                        const xwu8_t stream[], xwsz_t * size)
{
        xwsz_t i, total;
        xwu8_t byte, remainder;
        const xwu8_t * table;
        xwer_t rc;

        switch (plynml) {
#if defined(XWLIBCFG_CRC8_0X07) && (1 == XWLIBCFG_CRC8_0X07)
        case 0x7:
                table = xwlib_crc8tbl_0x07;
                break;
#endif /* XWLIBCFG_CRC8_0X07 */
#if defined(XWLIBCFG_CRC8_0X31) && (1 == XWLIBCFG_CRC8_0X31)
        case 0x31:
                table = xwlib_crc8tbl_0x31;
                break;
#endif /* XWLIBCFG_CRC8_0X31 */
#if defined(XWLIBCFG_CRC8_0X9B) && (1 == XWLIBCFG_CRC8_0X9B)
        case 0x9B:
                table = xwlib_crc8tbl_0x9B;
                break;
#endif /* XWLIBCFG_CRC8_0X9B */
        default:
                table = NULL;
                break;
        }
        if (table) {
                remainder = *crc8;
                total = *size;
                for (i = 0; i < total; i++) {
                        if (refin) {
                                byte = xwbop_rbit8(stream[i]);
                        } else {
                                byte = stream[i];
                        }
                        remainder = table[remainder ^ byte];
                }
                *crc8 = remainder;
                *size = 0;
                rc = XWOK;
        } else {
                rc = -EOPNOTSUPP;
        }
        return rc;
}

__xwlib_code
xwer_t xwlib_crc8_cal(xwu8_t * crc8,
                      xwu8_t xorout, bool refin, bool refout, xwu8_t plynml,
                      const xwu8_t stream[], xwsz_t * size)
{
        xwer_t rc;
        xwsz_t total, pos;
        xwu8_t res;

        XWOS_VALIDATE((crc8), "nullptr", -EFAULT);
        XWOS_VALIDATE((size), "nullptr", -EFAULT);

        total = *size;
        res = *crc8;
        pos = 0;
        /* 使用硬件计算部分CRC8校验值 */
        rc = soc_crc8_cal(&res, refin, plynml, &stream[0], size);
        if (*size) {
                /* 使用软件计算剩余部分的CRC8校验值 */
                pos = total - *size;
                rc = xwlib_crc8_swcal(&res, refin, plynml, &stream[pos], size);
                pos = total - *size;
        }/* else {} */
        if (XWOK == rc) {
                if (0 == *size) {
                        if (refout) {
                                res = xwbop_rbit8(res);
                        }/* else {} */
                        res = res ^ xorout;
                }/* else {} */
                *crc8 = res;
        }/* else {} */
        return rc;
}

__xwlib_code
xwu8_t xwlib_crc8_calms(const xwu8_t stream[], xwsz_t * size)
{
        xwu8_t result;

        result = 0x0;
        xwlib_crc8_cal(&result,
                       0x0, false, false, 0x07,
                       stream, size);
        return result;
}
