#!/bin/sh

scriptname=$(basename $0)
compilers="gcc-9 gcc-10 clang-9 clang-10 owcc nvc"
exe_dir=exe

docompile() {
    local compiler=$1
    local csource=$2
    local exe=${exe_dir}/$(basename ${csource} .c).${compiler}
    local opt_warns="-Wall -Wextra"
    local cstandard="-std=c11"
    local cincludes=-I../include
    local options=""
    local errors=0

    rm -fv ${exe} > ${compiler}.err >  ${compiler}.err
    case ${compiler} in
        gcc*)
            options="${cincludes} ${opt_warns} ${cstandard} -o ${exe}"
            ;;
        clang*)
            options="${cincludes} ${opt_warns} ${cstandard} -o ${exe}"
            ;;
        owcc)
            cstandard="-std=c99"
            options="${cincludes}  ${opt_warns} ${cstandard} -o ${exe}"
            ;;
        nvc)
            options="${cincludes} ${opt_warns} ${cstandard} -o ${exe}"
            ;;
        *)
            # TODO: it's an error!
            echo "${compiler}: unknown compiler" >> ${compiler}.err
            errors=1
            ;;
    esac
    if [ ${errors} -eq 0 ]
    then
        # echo "${compiler} ${options} ${CFLAGS} ${csource}"
        ${compiler} ${options} ${CFLAGS} ${csource} 2>> ${compiler}.err >> ${compiler}.err \
            || errors=1
    fi
    if [ ${errors} -ne 0 ]
    then
        echo "${compiler}: errors occur"
    else
        echo "${compiler}: OK"
    fi
}

dohelp() {
    local exitcode=0
    [ $# -eq 1 ] exitcode=$1
    echo "${scriptname} [-h|--help]: this text"
    echo "${scriptname} sourcec.c: compile sourcec.c with all these compilers: ${compilers}"
    exit ${exitcode}
}

compile_all() {
    local csource=$1
    mkdir -p ${exe_dir}
    for compiler in ${compilers}
    do 
        docompile ${compiler} ${csource}
    done
}

case $# in
    0)
        dohelp 
        ;;
    1)
        case $1 in
            -h|--help)
                dohelp
                ;;
            *)
                compile_all $1
                ;;
            *)
                echo "${scriptname}: unknown argument '${1}'"
                dohelp 1
                ;;
        esac
        ;;
    *)
        echo "${scriptname}: too much arguments"
        dohelp 1
        ;;
esac


