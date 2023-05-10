#! ./venv/bin/python


import argparse
import subprocess
import sys
import platform
import numpy as np
from ctypes import CDLL, c_float, c_int


from loguru import logger
import matplotlib.pyplot as plt
from exceptions import \
    TlbRuntimeException

page_count_c_lib = CDLL('./count.so')


def prepare_logger(log_level: str) -> None:
    logger.remove()
    logger.add(sink=sys.stderr, level=log_level)


def get_result_from_tlb(pages: int, trials: int, single_cpu: bool = False) -> float:
    run_process = []

    if single_cpu:
        run_process.extend(['taskset', '-c', '0'])
    run_process.extend(['./tlb', str(pages), str(trials)])

    process = subprocess.Popen(run_process,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE)
    output, err = process.communicate()
    if err:
        logger.error(f'TBL end with error message: {err.decode()}')
        raise TlbRuntimeException
    else:
        try:
            return float(output.decode())
        except ValueError:
            logger.error(f"Can't get float result from process output, OUTPUT:{output.decode()}")
            raise TlbRuntimeException


def get_result_from_tlb_lib(pages: int, trials: int) -> float:
    result = page_count_c_lib.get_pages_time
    result.restype = c_float
    return result(pages, trials)


def create_graph(x: np.array, y: np.array, pages_count) -> None:
    plt.xlabel("Number Of Pages")
    plt.ylabel("Time Per Access (ns)")
    plt.xticks(x, pages_count, fontsize="x-small")
    plt.plot(x, y)
    plt.show()


def main(pages: int, trials: int, single_cpu: bool, lib_counter: bool) -> None:
    x = np.arange(pages)
    pages_count = 2 ** x

    logger.debug(f'Generated_pages : {pages_count}')

    res_func = get_result_from_tlb_lib if lib_counter is True else get_result_from_tlb

    results = np.array([res_func(int(pages), int(trials)) for pages in pages_count])

    create_graph(x, results, pages_count)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--pages', type=int, help='Page number degree', default=4)
    parser.add_argument('-t', '--trials', type=int, help='Number of trials', default=10)
    parser.add_argument('-s', '--single_cpu', help='single CPU option, not work on MAC OS', action='store_true')
    parser.add_argument('-d', '--debug', help='Debug mode', action='store_true')
    parser.add_argument('-l', '--count_with_lib', help='Count with C module from python', action='store_true')
    args = parser.parse_args()
    logger_level = 'DEBUG' if args.debug else 'INFO'
    prepare_logger(logger_level)

    if args.single_cpu is False or platform.system() == 'Darwin':
        single_cpu_option = False
    else:
        single_cpu_option = True

    logger.info(f'Program start with [p: {args.pages}]'
                f' [t: {args.trials}]'
                f' [SINGLE_CPU: {single_cpu_option}]'
                f' [COUNT_WITH_LIB: {args.count_with_lib}]'
                f' [LOGGER_MODE: {logger_level}]')

    main(pages=args.pages,
         trials=args.trials,
         single_cpu=single_cpu_option,
         lib_counter=args.count_with_lib)

