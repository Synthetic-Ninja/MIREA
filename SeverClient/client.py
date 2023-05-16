import pickle
import socket
import argparse



def main(arguments: argparse.Namespace) -> None:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print(f'Try to send data to {arguments.target}\nx_min: {arguments.x_min};\nx_max: {arguments.x_max};')
    try:
        s.connect((arguments.target, arguments.port))
        s.sendall(pickle.dumps([arguments.x_min, arguments.x_max]))
        data = s.recv(1024)
        print(f'Message from server: {data.decode()}')
    except Exception as e:
        print(f'Error: {e}')


    
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-t', '--target', type=str, default='127.0.0.1', help='Target address exapmle: -t 127.0.0.1')
    parser.add_argument('-p', '--port', type=int, default=3030, help='Target port exapmle:  -p 3030')      # option that takes a value
    parser.add_argument('-x1', '--x_min', type=int, default=-10)
    parser.add_argument('-x2', '--x_max', type=int, default=11)
    args = parser.parse_args()
    main(args)

