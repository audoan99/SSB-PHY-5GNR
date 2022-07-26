INC += -I./inc/ \
	   -I./inc/SYNC_SIGNAL/ \
	   -I./inc/PAYLOAD_GENERATION \
	   -I./inc/SCRAMBLING \
	   -I./inc/CRC	\
	   -I./inc/CHANNEL_CODING \
	   -I./inc/RATE_MATCHING \
	   -I./inc/MODULATION \
	   -I./inc/RESOURCE_ELEMENT_MAPPING

SRC += ./src/SYNC_SIGNAL/*.c \
	   ./src/PAYLOAD_GENERATION/*.c \
	   ./src/SCRAMBLING/*.c \
	   ./src/CRC/*.c \
	   ./src/CHANNEL_CODING/*.c \
	   ./src/RATE_MATCHING/*.c \
	   ./src/MODULATION/*.c \
	   ./src/RESOURCE_ELEMENT_MAPPING/*.c \
	   ./src/*.c \
	   ./main.c

.PHONY: build run clean clean_log

build:
	@echo "Building Source Code 5G-L1 . . ."
	cc -g $(INC) $(SRC) -o main.out -lm
	@echo "Build Complete!"

run:
	./main.out

clean:
	rm *.out
	rm *.log

clean_log:
	rm *.log