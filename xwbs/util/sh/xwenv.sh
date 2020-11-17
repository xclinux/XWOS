#! /bin/sh
# @file
# @brief 编译xwmo的shell辅助函数
# @author
# + 隐星魂 (Roy.Sun) <https://xwos.tech>
# @copyright
# + (c) 2015 隐星魂 (Roy.Sun) <https://xwos.tech>
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

function xwmc()
{
  local cpath=$(pwd)
  echo ${XWOS_OEM_DIR}
  local rpath=
  local prefix=
  if [[ ${cpath} =~ ${XWOS_MD_DIR} ]] ; then
    rpath=${cpath#*${XWOS_MD_DIR}}
    prefix=XWMDCFG
  elif [[ ${cpath} =~ ${XWOS_CD_DIR} ]] ; then
    rpath=${cpath#*${XWOS_CD_DIR}}
    prefix=XWCDCFG
  elif [[ ${cpath} =~ ${XWOS_EM_DIR} ]] ; then
    rpath=${cpath#*${XWOS_EM_DIR}}
    prefix=XWEMCFG
  elif [[ ${cpath} =~ ${XWOS_AM_DIR} ]] ; then
    rpath=${cpath#*${XWOS_AM_DIR}}
    prefix=XWAMCFG
  elif [[ ${cpath} =~ ${XWOS_BM_DIR} ]] ; then
    rpath=${cpath#*${XWOS_BM_DIR}}
    prefix=BMCFG
  elif [[ ${cpath} =~ ${XWOS_OEM_DIR} ]] ; then
    rpath=${cpath#*${XWOS_OEM_DIR}}
    prefix=OEMCFG
  fi
  local cfg=${rpath//_/__}
  local cfg=${cfg//./_}
  local cfg=${cfg//-/_}
  local cfg=${prefix}${cfg//\//_}
  echo ${cfg}
}

function xwmn()
{
  local cpath=$(pwd)
  local rpath=
  local prefix=
  if [[ ${cpath} =~ ${XWOS_MD_DIR} ]] ; then
    rpath=${cpath#*${XWOS_MD_DIR}}
    prefix=xwmd
  elif [[ ${cpath} =~ ${XWOS_CD_DIR} ]] ; then
    rpath=${cpath#*${XWOS_CD_DIR}}
    prefix=xwcd
  elif [[ ${cpath} =~ ${XWOS_BM_DIR} ]] ; then
    rpath=${cpath#*${XWOS_BM_DIR}}
    prefix=xwbm
  elif [[ ${cpath} =~ ${XWOS_EM_DIR} ]] ; then
    rpath=${cpath#*${XWOS_EM_DIR}}
    prefix=xwem
  elif [[ ${cpath} =~ ${XWOS_AM_DIR} ]] ; then
    rpath=${cpath#*${XWOS_AM_DIR}}
    prefix=xwam
  elif [[ ${cpath} =~ ${XWOS_OEM_DIR} ]] ; then
    rpath=${cpath#*${XWOS_OEM_DIR}}
    prefix=xwoem
  fi
  local name=${rpath//_/__}
  local name=${rpath//./_}
  local name=${rpath//-/_}
  local name=${prefix}${name//\//_}.a
  echo ${name}
}

function xwm()
{
  local argv=$(getopt -o B -n "${0}" -- "$@")
  eval set -- "${argv}"
  local opt_b=false
  local opt_target=
  while true ; do
    case "$1" in
      -B)
        opt_b=true
        shift 1
        ;;
      --)
        opt_target=$2
        break
        ;;
    esac
  done

  if [[ ${opt_b} = true ]] ; then
    make -C ${XWOS_BRD_DIR} clean
  fi
  make -C ${XWOS_BRD_DIR} ${opt_target}
}

function xwmm()
{
  local argv=$(getopt -o B -n "${0}" -- "$@")
  eval set -- "${argv}"
  local opt_b=false
  while true ; do
    case "$1" in
      -B)
        opt_b=true
        shift 1
        ;;
      --)
        break
        ;;
    esac
  done

  local cpath=$(pwd)
  local rpath=${cpath#*${XWOS_PATH}/}
  if [[ ${opt_b} = true ]] ; then
    make -C ${XWOS_PATH} -f ${rpath}/xwmo.mk XWOS_BRD_DIR=${XWOS_BRD_DIR} clean
  fi
  make -C ${XWOS_PATH} -f ${rpath}/xwmo.mk XWOS_BRD_DIR=${XWOS_BRD_DIR}
}

function xwmmm()
{
  local argv=$(getopt -o B -n "${0}" -- "$@")
  eval set -- "${argv}"
  local opt_b=false
  local opt_mo=
  while true ; do
    case "$1" in
      -B)
        opt_b=true
        shift 1
        ;;
      --)
        opt_mo=${2}
        break
        ;;
    esac
  done

  local rpath=${opt_mo}
  if [[ ${opt_b} = true ]] ; then
    make -C ${XWOS_PATH} -f ${rpath}/xwmo.mk XWOS_BRD_DIR=${XWOS_BRD_DIR} clean
  fi
  make -C ${XWOS_PATH} -f ${rpath}/xwmo.mk XWOS_BRD_DIR=${XWOS_BRD_DIR}
}

function xwcroot()
{
  cd ${XWOS_PATH}
}

function xwcbd()
{
  cd ${XWOS_PATH}/${XWOS_BRD_DIR}
}
