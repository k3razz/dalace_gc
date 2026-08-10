# Dalace GC
> [!WARNING]
> Этот проект ещё не доделан, и не готов к глобальному использованию.

# Что это такое?
В играх Valve «Game Coordinator» (GC) — это серверный сервис, отвечающий, в первую очередь, за подбор игроков и управление инвентарём (например, комплектациями и скинами). Данный проект перенаправляет трафик GC на пользовательскую реализацию, работающую внутри процесса.

# Текущие функции
- Редактируемый список инвентаря (inventory.txt)
- Экипировка предметов
- Открытие ящиков (включая капсулы со стикерами, наборы нашивок, ящики с граффити и ящики с музыкальными наборами)
- Поддержка граффити
- Поддержка StatTrak для оружия
- Наклейки и нашивки
- Именные бирки
- Внутриигровой магазин
- Работает без полной эмуляции API Steam
- Полная поддержка Windows, Linux и macOS
- Рабочие лобби
- Поддержка выделенных серверов
- Рабочий браузер серверов (отображает только серверы csgo_gc)
- Сетевое взаимодействие с использованием P2P-интерфейса Steam

# Планируемые функции
- Остальные основные функции (обмен предметами, сувениры, замена StatTrak...)
- Графический редактор инвентаря
- Инструмент для копирования инвентаря из CS2

# Настройка инвентаря
Поскольку графического редактора пока нет, вам придётся редактировать файл `csgo_gc/inventory.txt` вручную.

## Лицензия
Этот проект находится под 2-Clause BSD лицензии. Посмотрите [LICENSE.md](LICENSE.md) для деталей.

## Благодарность
* **Mikko Kokko** - Автор

## Зависимости от сторонних компонентов
- [Crypto++](https://github.com/weidai11/cryptopp) ([Boost Software License](https://github.com/weidai11/cryptopp/blob/master/License.txt))
- [funchook](https://github.com/kubo/funchook) ([GPL v2 with Classpath Exception](https://github.com/kubo/funchook/blob/master/LICENSE))
- [diStorm3](https://github.com/gdabah/distorm) ([3-Clause BSD License](https://github.com/gdabah/distorm/blob/master/COPYING))
- [protobuf](https://github.com/protocolbuffers/protobuf) ([3-Clause BSD License](https://github.com/protocolbuffers/protobuf/blob/main/LICENSE))
