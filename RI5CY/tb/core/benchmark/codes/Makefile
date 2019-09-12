SUBDIRS = adpcm aes fft matrixmultiply

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: $(SUBDIRS)