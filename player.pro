HEADERS = mainwindow.h librarywidget.h playlistwidget.h playlistcontainermodel.h playlistmodel.h playlistcontainerlistview.h session.h qtsession.h logindialog.h search.h artist.h playlistcontainer.h playlist.h track.h

SOURCES = test.cpp mainwindow.cpp librarywidget.cpp playlistwidget.cpp playlistcontainermodel.cpp playlistmodel.cpp playlistcontainerlistview.cpp session.cpp appkey.cpp logindialog.cpp qtsession.cpp search.cpp artist.cpp playlistcontainer.cpp playlist.cpp track.cpp
TARGET = player
LIBS += -lspotify -L/Users/dag/Documents/Dev/libspotifycpp

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -g3
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -g3

QMAKE_POST_LINK += install_name_tool -change @loader_path/../Frameworks/libspotify.framework/libspotify /Users/dag/Documents/Dev/libspotifycpp/libspotify.so  player.app/Contents/MacOS/player

