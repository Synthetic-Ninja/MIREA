# Установка
1. *Создать папку
2. *Установить виртуальное окружение и активировать его


### Windows

Для создания виртуального окружения на Windows необходимо использовать следующие команды из командной строки:


#### Создание виртуального окружения
~~~sh
python -m venv myenv
~~~

#### Активация виртуального окружения
~~~sh
myenv\Scripts\activate.bat
~~~


### macOS и Linux

Для создания виртуального окружения на macOS или Linux необходимо использовать следующие команды из терминала:


#### Создание виртуального окружения
~~~sh
python -m venv myenv
~~~

#### Активация виртуального окружения
~~~sh
source myenv/bin/activate
~~~

После выполнения этих команд виртуальное окружение с именем myenv будет активировано, и все последующие команды для установки пакетов и запуска Python будут выполняться в его контексте.

Независимо от операционной системы, чтобы выйти из виртуального окружения, нужно выполнить команду `deactivate`

3. *Находясь в виртуальном окружении становить зависимости командой 'pip install -r reqiurements.txt'



# Запуск

1. Запустить server.py 
	Необязательные параметры
	-ip задает ip сервера, по умолчанию 127.0.0.1
	-p задает порт сервера, по умолчанию 3030

2. Запустить client.py
	
