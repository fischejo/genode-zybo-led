# \brief  Non-Generic LED Driver for Zybo
# \author Johannes Fischer
# \date   2018-12-15

TARGET   = led_drv

SRC_CC   = main.cc
#LIBS     = base stdcxx
LIBS     = base
INC_DIR += $(PRG_DIR)

vpath main.cc $(PRG_DIR)

CC_CXX_WARN_STRICT =
