#! /bin/make -f
# @file
# @brief Top makefile of board/project
# @author
# + 隐星魂 (Roy Sun) <xwos@xwos.tech>
# @copyright
# + Copyright © 2015 xwos.tech, All Rights Reserved.
# > Licensed under the Apache License, Version 2.0 (the "License");
# > you may not use this file except in compliance with the License.
# > You may obtain a copy of the License at
# >
# >         http://www.apache.org/licenses/LICENSE-2.0
# >
# > Unless required by applicable law or agreed to in writing, software
# > distributed under the License is distributed on an "AS IS" BASIS,
# > WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# > See the License for the specific language governing permissions and
# > limitations under the License.
#

XWOS ?= ../..
WKSPC ?= wkspc
TARGET ?= XWOS

MKCFG := ${XWOS}/xwbs/util/el/mkcfg.el

all: $(WKSPC) cfg dbgcfg
	$(MAKE) -C $(WKSPC) TARGET=$(TARGET)

$(WKSPC):
	@mkdir -p $@

cfg: $(WKSPC) $(WKSPC)/XuanWuOS.cfg

$(WKSPC)/XuanWuOS.cfg: cfg/*.h
	@[ -x ${MKCFG} ] || chmod +x ${MKCFG}
	@${MKCFG} --XWOS=$(XWOS) --cfgdir=cfg --wkspc=$(WKSPC) -- $(@F)

dbgcfg: cfg/dbg/debug.gdb cfg/dbg/program.gdb cfg/dbg/erase.gdb

%.gdb: %.gdb.template
	@sed "s/##DIR##/$(subst /,\\/,$(shell pwd)/$(WKSPC))/g" $< > $@

jlink:
	@openocd -f cfg/dbg/openocd/jlink-swd.cfg

cmdap:
	@openocd -f cfg/dbg/openocd/cmsis-dap.cfg

dbg: cfg/dbg/debug.gdb
	@arm-none-eabi-gdb -x cfg/dbg/debug.gdb

pgm: cfg/dbg/program.gdb
	@arm-none-eabi-gdb -x cfg/dbg/program.gdb

erase: cfg/dbg/erase.gdb
	@arm-none-eabi-gdb -x cfg/dbg/erase.gdb

c clean: cfg
	$(MAKE) -C $(WKSPC) TARGET=$(TARGET) NODEP=y clean

d distclean: cfg
	@rm -rf $(WKSPC)
	@rm -rf cfg/dbg/*.gdb

.DEFAULT:
	@$(MAKE) cfg
	$(MAKE) -C $(WKSPC) TARGET=$(TARGET) $@

.PHONY : all cfg dbgcfg c clean d distclean
