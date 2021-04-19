set (events_src

    ApplicationEvent.hpp
    Events.hpp
    KeyEvent.hpp
    MouseEvent.hpp
    )


#add_library(events INTERFACE)
#target_sources(events INTERFACE ${events_src})

#target_include_directories(events
    #INTERFACE 
    #${CMAKE_CURRENT_SOURCE_DIR}
#)


add_source("${events_src}")
