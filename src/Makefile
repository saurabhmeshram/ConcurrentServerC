SERVER_SRC_PATH = $(FTP_PATH)/src/server/
CLIENT_SRC_PATH = $(FTP_PATH)/src/client/

INCLUDE_PATH = $(FTP_PATH)/include/
OBJECT_PATH = $(FTP_PATH)/obj/

SERVER_SRC= $(SERVER_SRC_PATH)server_main.c
SERVER_OBJ= $(SERVER_SRC:c=o)

CLIENT_SRC= $(CLIENT_SRC_PATH)client_main.c
CLIENT_OBJ= $(CLIENT_SRC:c=o)

.PHONY: all $(TARGET_SERVER) $(TARGET_CLIENT) clean

all: 	$(TARGET_SERVER) $(TARGET_CLIENT)
	@echo "Done."
	@echo "Binaries genarated at [$(FTP_PATH)/bin/] "

# Building SERVER TARGET #
$(TARGET_SERVER): 	$(SERVER_OBJ)
			@echo "Building Server Binary"
			@$(CC) $(CFLAGS) -o $(TARGET_SERVER) $(SERVER_OBJ)
			@$(MV) $(TARGET_SERVER) $(FTP_PATH)/bin/

$(SERVER_OBJ): 		$(SERVER_SRC)
			@$(CC) $(CFLAGS) -c $(SERVER_SRC) -o $(SERVER_OBJ) -I $(INCLUDE_PATH)


# Building CLIENT TARGET #
$(TARGET_CLIENT):	$(CLIENT_OBJ)
			@echo "Building Client Binary"
			@$(CC) $(CFLAGS) -o $(TARGET_CLIENT) $(CLIENT_OBJ)
			@$(MV) $(TARGET_CLIENT) $(FTP_PATH)/bin/

$(CLIENT_OBJ):		$(CLIENT_SRC)
			@$(CC) $(CFLAGS) -c $(CLIENT_SRC) -o $(CLIENT_OBJ) -I $(INCLUDE_PATH)

clean:
	@$(RM) -rf $(FTP_PATH)/bin/server_obj/* $(FTP_PATH)/bin/client_obj/* $(FTP_PATH)/bin/$(TARGET_SERVER) $(FTP_PATH)/bin/$(TARGET_CLIENT)
