QT_ROOT := C:/Qt
QT_PATH := C:/Qt/6.0.0/mingw81_64
GUI_CXX_FLAGS_COMPILE := -c -std=gnu++1z
GUI_CXX_FLAGS_LINK := -lmingw32
TARGET := .build/bin/life.exe

rsearch = $(strip $(foreach filename,$(wildcard $(1)/*),$(call rsearch,$(filename),$(2)) $(filter $(subst *,%,$(2)),$(wildcard $(filename)))))
win_form = $(subst /,\,$(1))

HEADERS := \
$(addprefix -I, \
$(patsubst %/,%,$(sort $(dir $(call rsearch,$(QT_PATH)/include,*.h) \
$(call rsearch,.,*.h)))) \
$(QT_PATH)/include\
)

RESOURCES := $(wildcard resources/*)

BUILD_RESOURCES := $(addprefix .build/bin/,$(RESOURCES))

ARCH_LIBS := $(subst /,\,$(call rsearch,$(QT_PATH)/lib,*.a))
GUI_SOURCES := $(call rsearch,./gui,*cpp)
GUI_OBJECTS := $(subst .cpp,.o,$(subst ./,./.build/,$(GUI_SOURCES)))

SRC_SOURCES := $(call rsearch,./src,*cpp)
SRC_OBJECTS := $(subst .cpp,.o,$(subst ./,./.build/,$(SRC_SOURCES)))

.PHONY: all

all: build

build: $(TARGET) $(BUILD_RESOURCES)
	set TEMP_PATH=%PATH%
	set PATH=$(call win_form,$(QT_PATH)/bin;$(QT_ROOT)/Tools/mingw810_64/bin;)%PATH% && windeployqt $(call win_form,$(TARGET))
	set PATH=%TEMP_PATH%
	set TEMP_PATH=

$(TARGET): $(GUI_OBJECTS) $(SRC_OBJECTS)
	g++ $(call win_form,$^) $(GUI_CXX_FLAGS_LINK) $(ARCH_LIBS) -o $(call win_form,$@)

./.build/gui/%.o: gui/%.cpp
	g++ $(GUI_CXX_FLAGS_COMPILE) $(HEADERS) $(call win_form,$<) -o $(call win_form,$@)

./.build/src/%.o: src/%.cpp
	g++ $(GUI_CXX_FLAGS_COMPILE) $(HEADERS) $(call win_form,$<) -o $(call win_form,$@)

.build/bin/resources/%:
	copy resources\* .build\bin\resources
