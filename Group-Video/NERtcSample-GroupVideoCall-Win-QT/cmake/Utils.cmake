#** source group by dir *********************************************************************************
macro(source_group_by_dir source_files)
    if(MSVC)
        #
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        #
        foreach(sgbd_file ${${source_files}})
            #
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            #
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif()
            #
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach()
    endif()
endmacro(source_group_by_dir)