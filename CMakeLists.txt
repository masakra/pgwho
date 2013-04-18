project( pgwho )

find_package( KDE4 REQUIRED )
include( KDE4Defaults )
#find_package( Plasma REQUIRED )

add_definitions ( ${QT_DEFINITIONS} ${KDE4_DEFINITIONS} )
include_directories( ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES} )

set( pgwho_SRCS src/PgWho.cpp src/WidgetConfig.cpp )

kde4_add_plugin( plasma_pgwho ${pgwho_SRCS} )
target_link_libraries( plasma_pgwho ${PLASMA_LIBS} ${KDE4_KDEUI_LIBS} ${QT_QTSCRIPT_LIBRARY} )

install( TARGETS plasma_pgwho DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES plasma-pgwho.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
