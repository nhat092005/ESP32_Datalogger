set(srcs "datalogger.c")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "."
                    REQUIRES driver freertos i2c_utils bh1750 sht31)