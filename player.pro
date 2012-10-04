HEADERS = mainwindow.h session.h qtsession.h logindialog.h search.h artist.h playlistcontainer.h

SOURCES = test.cpp mainwindow.cpp session.cpp appkey.cpp logindialog.cpp qtsession.cpp search.cpp artist.cpp playlistcontainer.cpp
TARGET = player
LIBS += -lspotify -L.

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -g3
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -g3

QMAKE_POST_LINK += install_name_tool -change @loader_path/../Frameworks/libspotify.framework/libspotify @executable_path/../../../libspotify.so  player.app/Contents/MacOS/player

