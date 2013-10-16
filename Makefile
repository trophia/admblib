#
# A Makefile
# Since this is currently a header only library
# all it does right now is install ADMB

ADMB_VERSION=11.1

# Make and install ADMB on this machine
# "It is recommended to build ADMB from source to best match compiler and operating system"
# This is mostly based on the offfical Unix installation instructions at http://www.admb-project.org/svn/tags/admb-11.1/INSTALL.txt
admb: admb-$(ADMB_VERSION).zip
	unzip admb-$(ADMB_VERSION).zip
	cd admb; make

# Get ADMB source
admb-$(ADMB_VERSION).zip:
	wget http://admb-project.googlecode.com/files/admb-$(ADMB_VERSION).zip
