/**
 * @file
 * @brief STM32CUBE：FatFS的SD卡驱动
 * @author
 * + 隐星魂 (Roy.Sun) <https://xwos.tech>
 * @copyright
 * + (c) 2015 隐星魂 (Roy.Sun) <https://xwos.tech>
 * > Licensed under the Apache License, Version 2.0 (the "License");
 * > you may not use this file except in compliance with the License.
 * > You may obtain a copy of the License at
 * >
 * >         http://www.apache.org/licenses/LICENSE-2.0
 * >
 * > Unless required by applicable law or agreed to in writing, software
 * > distributed under the License is distributed on an "AS IS" BASIS,
 * > WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * > See the License for the specific language governing permissions and
 * > limitations under the License.
 */

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      include      ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
#include <bm/stm32cube/standard.h>
#include <xwem/fs/fatfs/ff.h>
#include <bm/stm32cube/cubemx/Core/Inc/sdio.h>

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********      macros       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       types       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ******** ********       .data       ******** ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********         function prototypes         ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/

/******** ******** ******** ******** ******** ******** ******** ********
 ******** ********      function implementations       ******** ********
 ******** ******** ******** ******** ******** ******** ******** ********/
int MMC_disk_status(void)
{
        return (int)MX_SDIO_SD_GetState();
}

int MMC_disk_initialize(void)
{
        int rc;

        if (HAL_SD_STATE_READY == hsd.State) {
                rc = XWOK;
        } else {
                rc = MX_SDIO_SD_TrimClk(10);
        }
        return (int)rc;
}

int MMC_disk_read(uint8_t * buff, uint64_t sector, uint32_t count)
{
        xwer_t rc;

        rc = MX_SDIO_SD_Read(buff, (uint32_t)sector, count);
        return (int)rc;
}

int MMC_disk_write(uint8_t * buff, uint64_t sector, uint32_t count)
{
        xwer_t rc;

        rc = MX_SDIO_SD_Write(buff, (uint32_t)sector, count);
        return (int)rc;
}

int MMC_disk_ioctl(uint8_t cmd, void * buff)
{
        int rc;

        switch (cmd) {
        case CTRL_SYNC:
                rc = XWOK;
                break;
        case GET_SECTOR_COUNT:
                *(uint32_t *)buff = (hsd.SdCard.BlockSize * hsd.SdCard.BlockNbr) / MX_SD_SECTOR_SIZE;
                rc = XWOK;
                break;
        case GET_SECTOR_SIZE:
                *(uint16_t *)buff = MX_SD_SECTOR_SIZE;
                rc = XWOK;
                break;
        case GET_BLOCK_SIZE:
                *(uint32_t *)buff = hsd.SdCard.BlockSize;
                rc = XWOK;
                break;
        case CTRL_TRIM:
                rc = XWOK;
                break;
        default:
                rc = -EINVAL;
                break;
        }
        return (int)rc;
}
