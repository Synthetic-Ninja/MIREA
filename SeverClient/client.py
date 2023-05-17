import pickle
import socket
import tkinter
from functools import partial


def send_data(ip: tkinter.Label,
              port: tkinter.Label,
              x_min: tkinter.Label, 
              x_max: tkinter.Label,
              info_label: tkinter.Label) -> None:
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        s.connect((ip.get(), int(port.get())))
        s.sendall(pickle.dumps([int(x_min.get()), int(x_max.get())]))
        data = s.recv(1024)
        info_label['text'] = f'Message from server: {data.decode()}'
    except Exception as e:
        info_label['text'] = f'Error: {e}'


def main() -> None:
    root = tkinter.Tk()
    
    default_ip = tkinter.StringVar()
    default_ip.set("127.0.0.1")

    default_port = tkinter.StringVar()
    default_port.set("3030")

    default_x_min = tkinter.StringVar()
    default_x_min.set("-10")

    default_x_max = tkinter.StringVar()
    default_x_max.set("15")


    label1 = tkinter.Label(root, text="Введите ip:")
    label1.pack()
    entry1 = tkinter.Entry(root, textvariable=default_ip)
    entry1.pack(padx=10, pady=5)
    
    label2 = tkinter.Label(root, text="Введите порт:")
    label2.pack()
    entry2 = tkinter.Entry(root, textvariable=default_port)
    entry2.pack(padx=10, pady=5)
    
    label3 = tkinter.Label(root, text="Введите x_min:")
    label3.pack()
    entry3 = tkinter.Entry(root, textvariable=default_x_min)
    entry3.pack(padx=10, pady=5)
    
    label4 = tkinter.Label(root, text="Введите x_max:")
    label4.pack()
    entry4 = tkinter.Entry(root, textvariable=default_x_max)
    entry4.pack(padx=10, pady=5)

    info_label = tkinter.Label(root, text="")
    info_label.pack()


    button_command = partial(send_data,
                             ip=entry1,
                             port=entry2,
                             x_min=entry3,
                             x_max=entry4,
                             info_label=info_label)
    
    button_submit = tkinter.Button(root, text="Отправить", command=button_command)
    button_submit.pack(pady=10)
    
    root.mainloop()

    
if __name__ == '__main__':
    main()

