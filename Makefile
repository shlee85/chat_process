TOP := .

DIR_OBJS = $(TOP)/obj
DIR_SRCS = $(TOP)/src

SRCS +=\
	$(DIR_SRCS)/chat_serv.cpp\
	$(DIR_SRCS)/socket_proc.cpp

#OBJS += $(foreach SRCS, $(SRCS), $(DIR_OBJS)/$(SRCS:.cpp=.o))
OBJS += $(foreach SRCS, $(SRCS), $(SRCS:.cpp=.o))

TARGET=chatd

CPPFLAGS= -lpthread -Wno-write-string -std=c++11

LIBS=
LIB_DIRS=

INC=./include

CPPFLAGS += $(addprefix -I,$(INC))

Q_ = @
ECHO = $(Q_)echo

CPP=g++

$(warning 'Compiling file1 : $<')

$(DIR_OBJS)/%.o: %.cpp
	$(ECHO) 'Compiling file2 : $<'
	$(Q_)$(CPP) $(DIR_INC) $(CPPFLAGS) -c -fmessage-length=0 -MMD -MP -MF "$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

all chat_process: $(TARGET)
	mv src/*.o obj/.
	#$(CPP) $(CPPFLAGS) -c $< -o $@ #compile

$(TARGET) : $(OBJS)
	$(CPP) $(OBJS) $(CPPFLAGS) -o $@

clean:
	rm -rf $(TARGET)
	rm -rf $(DIR_OBJS)/*.o
	rm -rf $(DIR_SRCS)/*.o
