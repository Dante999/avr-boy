$(MAKE)=make

.PHONY: all handheld cartridge flash_handheld flash_cartridge


all: handheld cartridge size
#
handheld:
	make -C handheld clean hex
#
cartridge:
	make -C cartridge clean hex

flash_handheld:
	make -C handheld

flash_cartridge:
	make -C cartridge

size:
	@echo "\n##################################################################"
	@echo "# HANDHELD\n"
	make -C handheld size
	@echo "\n##################################################################"
	@echo "# CARTRIDGE\n"
	make -C cartridge size
