TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
engine_eht/event/event.cpp \
engine_eht/eh/eventhandler.cpp \
engine_eht/task/task.cpp \
engine_eht/event/test/eventtest.cpp \
engine_eht/task/test/tasktest.cpp \
engine_eht/eh/test/eventhandlertest.cpp \
multithread/threadpool.cpp \
    general/loop.cpp \
    network/socket.cpp \
    engine_eht/eh/network/ehnetworkloop.cpp \
    engine_eht/event/network/eventstreamsocketaccepted.cpp \
    engine_eht/event/network/event_socket_ready_to_accept.cpp \
    network/server_socket_loop.cpp \
    network/server_socket.cpp \
    engine_eht/task/task_handle_event.cpp \
    engine_eht/event/network/event_network_accept_failed.cpp \
    network/pipeinterruptor.cpp \
    network/loop_socket_write.cpp

HEADERS += \
engine_eht/task/taskfwd.h \
engine_eht/task/test/tasktest.h \
engine_eht/task/task.h \
engine_eht/event/eventfwd.h \
engine_eht/event/test/eventtest.h \
engine_eht/event/event.h \
engine_eht/eh/test/eventhandlertest.h \
engine_eht/eh/test/ehtest.h \
engine_eht/eh/eventhandler.h \
engine_eht/eh/eventhandlerfwd.h \
general/runnable.h \
multithread/threadpool.h \
    general/loop.h \
    network/socket.h \
    engine_eht/eh/network/ehnetworkloop.h \
    engine_eht/event/network/eventstreamsocketaccepted.h \
    engine_eht/event/network/event_socket_ready_to_accept.h \
    network/server_socket_loop.h \
    network/server_socket.h \
    multithread/shared_queue.h \
    engine_eht/task/task_handle_event.h \
    engine_eht/event/network/event_network_accept_failed.h \
    network/pipeinterruptor.h \
    network/loop_socket_write.h



QMAKE_CXXFLAGS += -std=c++11
LIBS += /usr/lib/libboost_thread.so.1.49.0
