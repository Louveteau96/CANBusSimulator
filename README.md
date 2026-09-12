# 🚗 CAN Bus Simulator

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Unity](https://img.shields.io/badge/Tests-Unity-green.svg)](https://github.com/ThrowTheSwitch/Unity)

**Projet d'entraînement en C++ et systèmes embarqués** : Une simulation de bus CAN avec tests unitaires, réalisé avec l'aide de l'IA pour apprendre les bonnes pratiques de développement.

---

## 📌 À propos du projet

Ce projet est une **simulation logicielle d'un bus CAN** (Controller Area Network), un protocole de communication largement utilisé dans l'industrie automobile et embarquée. Il a été développé dans le cadre d'un **apprentissage du C++ moderne** et des concepts de **programmation embarquée**, avec un focus particulier sur :

- La **gestion de la concurrence** (threads, mutex)
- La **communication inter-processus** (simulation de messages CAN)
- Les **tests unitaires** avec le framework **Unity** (standard en embarqué)
- L'**architecture logicielle** (séparation des responsabilités)

> ⚠️ **Note** : Ce projet a été réalisé **avec l'aide d'une IA** (pour la structure, les corrections de bugs et les bonnes pratiques). L'objectif était d'apprendre en collaborant avec un outil d'assistance, tout en comprenant chaque partie du code.

---

---

## 🏗️ Structure du projet

```text
CANBusSimulator/
├── src/                  # Code source principal
│   ├── can_bus.cpp       # Implémentation de la classe CANBus
│   ├── can_bus.hpp       # Déclaration de la classe CANBus
│   ├── can_message.cpp   # Implémentation de la structure CANMessage
│   └── can_message.hpp   # Déclaration de la structure CANMessage
│
├── tests/                # Tests unitaires
│   ├── test_runner.cpp   # Point d'entrée des tests
│   ├── can_bus_test.cpp  # Tests pour CANBus
│   ├── can_message_test.cpp # Tests pour CANMessage
│   ├── unity.h           # Framework de test Unity
│   ├── unity.c           # Implémentation de Unity
│   └── unity_internals.h # Dépendances internes de Unity
│
├── Makefile             # Script de compilation (mingw32-make)
├── .gitignore           # Fichiers à exclure de Git
└── README.md            # Ce fichier
