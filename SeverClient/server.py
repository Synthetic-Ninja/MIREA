import pickle
import socket
import matplotlib.pyplot as plt
import argparse

def draw_graph(range_x: tuple) -> None:
    """Функция рисует график"""
    
    x = range(*range_x)
    y = [i ** 2 for i in x]
    plt.plot(x, y)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('y = x^2')
    plt.grid(True)
    plt.show()


def main(arguments: argparse.Namespace) -> None:
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
        server.bind((arguments.address, arguments.port))
        server.listen(1)
        print('Server started:\nIP = {0}\nPORT = {1}'.format(*server.getsockname())) 
        while True:
            conn, addr = server.accept()
            try:
                data = conn.recv(2048)
                draw_graph(pickle.loads(data))
                conn.sendall(b'Done!')
                break
                conn.close()
            except Exception as err:
                conn.sendall(f'Error: {err}'.encode())
                conn.close()
            
    except Exception as e:
        print(f'Error catched: {e}')
    finally:
        server.close()
        print('Server stopped!')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-ip', '--address', type=str, default='127.0.0.1', help='ip for server example: -ip 127.0.0.1')
    parser.add_argument('-p', '--port', type=int, default=3030, help='port for server example: -p 3030')
    args = parser.parse_args()
    try:
        main(args)
    except Exception as run_err:
        print(f'RuntimeError: {run_err}')
        exit()
