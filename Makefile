CFLAGS = -Iextern/
LDLIBS  = -lm -fopenmp
TARGET = stegdir

SRCS = 	src/stegdir.c \
	src/stegdir-encode.c \
	src/stegdir-decode.c \
	codegen/lib/matlab_base64/base64Encode.c \
	codegen/lib/matlab_base64/base64Decode.c \
	codegen/lib/matlab_base64/matlab_base64_data.c \
	codegen/lib/matlab_base64/matlab_base64_emxAPI.c \
	codegen/lib/matlab_base64/matlab_base64_emxutil.c \
	codegen/lib/matlab_base64/matlab_base64_initialize.c \
	codegen/lib/matlab_base64/matlab_base64_terminate.c \
	codegen/lib/matlab_base64/mod.c \
	codegen/lib/matlab_base64/repelem.c \
	codegen/lib/matlab_base64/validator_check_size.c

all: $(TARGET)


$(TARGET): $(SRCS)
	gcc $(CFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -rf $(TARGET)


