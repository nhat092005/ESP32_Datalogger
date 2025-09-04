idf_component_register(SRCS "datalogger.c"
                    PRIV_REQUIRES spi_flash
                    INCLUDE_DIRS "")

# idf_component_register(SRCS "datalogger.c"
#                     INCLUDE_DIRS "."
#                     REQUIRES driver freertos)