# Mario

## first problem - the default library link of cocos in ubuntu is too simple
```
INCLUDES +=	 -I../ \
	-I../Classes \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I$(COCOS_ROOT)/extensions/ \
	-I$(COCOS_ROOT)/external/ \
        -I$(COCOS_ROOT)/external/chipmunk/include/chipmunk
        
SHAREDLIBS += -lcocos2d -lcocosdenshion -lcurl -lpthread
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libcocosdenshion.so

STATICLIBS += \
        $(LIB_DIR)/libextension.a \
        $(LIB_DIR)/libbox2d.a \
        $(LIB_DIR)/libchipmunk.a
```
## second problem - undefine symbol of GLEnable, but I did link GL library
```
$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -Wl,--no-as-needed -o $@ $(SHAREDLIBS) $(STATICLIBS)
```
--no-as-needed: make all the library part in the build process. forbid compiler's error optimization from ignorning -lGL param
