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
engine_eht/task/task_handle_event.cpp \
general/loop.cpp \
multithread/threadpool.cpp \
network/socket.cpp \
network/server_socket_loop.cpp \
network/server_socket.cpp \
network/pipeinterruptor.cpp \
network/loop_socket_write.cpp \
network/events.cpp \
network/ehsocketloop.cpp \
    exceptions/exceptions.cpp

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
engine_eht/task/task_handle_event.h \
general/runnable.h \
general/loop.h \
multithread/threadpool.h \
multithread/shared_queue.h \
network/events.h \
network/pipeinterruptor.h \
network/loop_socket_write.h \
network/ehsocketloop.h \
network/socket.h \
network/server_socket_loop.h \
network/server_socket.h \
    log/log.h \
    exceptions/exceptions.h


QMAKE_CXXFLAGS += -std=c++11
LIBS += /usr/lib/libboost_thread.so.1.49.0
