ifneq ($(words $(CURDIR)),1)
 $(error Unsupported: GNU Make cannot build in directories containing spaces, build elsewhere: '$(CURDIR)')
endif

# Makefile for VPI integration.

######################################################################

CPP_COMPILER = gcc
CPP_LINKER_CMD = ar ruv
GHDL_CMD = ghdl

GHDL_BAD_LIB_ARGS = --ieee=synopsys -fexplicit
GHDL_WORK_DIR = ghdl_work

VPI_FILES_LOCATION = vpi_files/
OBJECTS = $(VPI_FILES_LOCATION)VpiMain.o $(VPI_FILES_LOCATION)Serial.o
LINKED_LIB_FILE = libmysim.a
VDHL_FILES = *.vhd $(VPI_FILES_LOCATION)/*.vhd

VHDL_UNIT = P6502_RAM_tb

######################################################################

default: $(OBJECTS)
	@mkdir $(GHDL_WORK_DIR)
	@echo "\e[0;33m// LINKING ///////////////////\e[0m"
	$(CPP_LINKER_CMD) $(LINKED_LIB_FILE) $(OBJECTS)
	@echo "\e[0;33m// GHDL ANALYZE //////////////\e[0m"
	$(GHDL_CMD) -i $(GHDL_BAD_LIB_ARGS) --workdir=$(GHDL_WORK_DIR) $(VDHL_FILES)
	@echo "\e[0;33m// GHDL ELABORATE ////////////\e[0m"
	$(GHDL_CMD) -m -Wl,$(LINKED_LIB_FILE) --workdir=$(GHDL_WORK_DIR) $(GHDL_BAD_LIB_ARGS) $(VHDL_UNIT)
	@echo "\e[0;33m// DONE //////////////////////\e[0m"
	@echo "Runnable file created: $(VHDL_UNIT)"

######################################################################

clean:
	-rm -rf *.a *.o *.cf
