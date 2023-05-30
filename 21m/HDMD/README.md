# Домашнее задание по Демиду 2023

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
    ```