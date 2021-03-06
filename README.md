[![Ubuntu](https://github.com/LvalueReference/vk-cli/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/LvalueReference/vk-cli/actions/workflows/ubuntu.yml)
[![MacOS](https://github.com/LvalueReference/vk-cli/actions/workflows/macos.yml/badge.svg)](https://github.com/LvalueReference/vk-cli/actions/workflows/macos.yml)
[![Windows](https://github.com/LvalueReference/vk-cli/actions/workflows/windows.yml/badge.svg)](https://github.com/LvalueReference/vk-cli/actions/workflows/windows.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/lvaluereference/vk-cli/badge)](https://www.codefactor.io/repository/github/lvaluereference/vk-cli)

# vk-cli
Программа для вывода сообщений из чата вк вам в консоль, которая полностью написана на **C++**

```shell
git clone --recursive https://github.com/LvalueReference/vk-cli.git
```

# Подготовка
#### Создать группу вк и скопировать из неё данные для работы с **VK API**:
1. Перейти по [**этой**](https://vk.com/groups?w=groups_create) ссылке и создать группу вк
2. Далее зайти в *управление* группой и во вкладке **настройки** под полем для ввода адреса будет текст "*Номер сообщества — **clubXXXXXXXXX.**"
Нас интересуют 9 цифр после "club" и до точки. Скопируйте эти цифры
3. Перейти во вкладку **Работа с API** и создать новый *ключ доступа* со всеми правами. Скопируйте этот ключ 
#### Добавить бота в группу:
1. В настройках бота перейти во вкладку `Сообщения -> Настройки для бота`, тыкнуть на галочку рядом с полем 
   **"Разрешать добавлять сообщество в беседы"** и сохранить изменения
2. Добавить бота в вашу беседу с помощью кнопки, которая появилась на главной странице вашей группы
3. Настройка конфиг-файла
   - Перейти по директории `config/` и редактировать файл `config.json`
   - Заполните конфиг данными, которые вы копировали из *пункта 1*
   - В поле `API_V` нужно указать последнюю версию **VK Api**, узнать её можно [**здесь**](https://vk.com/dev/versions)

# Установка библиотек 
OS | Command
---|---
Windows | ```vcpkg install curl[openssl]:x64-windows``` |
MacOS | ```brew install curl``` |
Debian-based дистрибутивы | ```sudo apt install cmake libcurl4 libcurl4-openssl-dev ``` |
Arch-based дистрибутивы | ```sudo pacman -Sy cmake libcurl4 libcurl4-openssl-dev``` |

### vcpkg
1. Установить vcpkg, следуя инструкции из официальной [**статьи**](https://github.com/microsoft/vcpkg#quick-start-windows)
2. ```shell
   vcpkg integrate install
   ```
# Сборка
1. Windows
```shell
mkdir build; cd build; cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg.cmake; cmake --build .
vkreader.exe
```
2. Linux / MacOS
```shell
mkdir build && cd build && cmake .. && cmake --build .
./vkreader
```
