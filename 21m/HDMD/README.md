# Домашнее задание по Демиду 2023
## Hooking in Linux using ftrace + kernel sysfs: Hide port

* Test:

    ```sh
    make
    make install
    cd /sys/kernel/hide/port
    netstat -tulnp                                     
    sudo su                                            
    sudo echo "631" > /sys/kernel/hide/port/add        
    cat list
    netstat -tulnp
    sudo echo "631" > /sys/kernel/hide/port/del     
    netstat -tulnp
    make uninstall
    make clean  
    ```