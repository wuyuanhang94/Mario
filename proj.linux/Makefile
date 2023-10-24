EXECUTABLE = Mario

INCLUDES += -I../ \
	-I../Classes \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I$(COCOS_ROOT)/extensions/ \
	-I$(COCOS_ROOT)/external/ \
	-I$(COCOS_ROOT)/external/chipmunk/include/chipmunk

SOURCES = main.cpp \
	../Classes/AppDelegate.cpp \
        ../Classes/LayerStart.cpp \
        ../Classes/LayerMenu.cpp \
        ../Classes/MyTableView.cpp \
        ../Classes/LayerGame.cpp \
        ../Classes/Mario.cpp \
#	../Classes/Hero.cpp \
#	../Classes/Enemy.cpp \
#	../Classes/Bullet.cpp \
#	../Classes/AI.cpp \
#        ../Classes/SceneScore.cpp \

COCOS_ROOT = ../../..
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lcocosdenshion -lcurl -lpthread
SHAREDLIBS += -lGL -lglut
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libcocosdenshion.so

STATICLIBS += \
	$(LIB_DIR)/libextension.a \
	$(LIB_DIR)/libbox2d.a \
	$(LIB_DIR)/libchipmunk.a \

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	@echo $(STATICLIBS)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -Wl,--no-as-needed -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
