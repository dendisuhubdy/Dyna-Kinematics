#include <QtWidgets/QApplication>
#include <QFile>
#include <QTextStream>
#include <QStyleFactory>

#include <iostream>

#include "rigid_body_simulator.h"
#include "game.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#endif

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   a.setStyle(QStyleFactory::create("Fusion"));

   // Modify palette to dark
   QPalette darkPalette;
   darkPalette.setColor(QPalette::Window,          QColor(53, 53, 53));
   darkPalette.setColor(QPalette::WindowText,      Qt::white);
   darkPalette.setColor(QPalette::Disabled,        QPalette::WindowText, QColor(127, 127, 127));
   darkPalette.setColor(QPalette::Base,            QColor(42, 42, 42));
   darkPalette.setColor(QPalette::AlternateBase,   QColor(66, 66, 66));
   darkPalette.setColor(QPalette::ToolTipBase,     Qt::white);
   darkPalette.setColor(QPalette::ToolTipText,     Qt::white);
   darkPalette.setColor(QPalette::Text,            Qt::white);
   darkPalette.setColor(QPalette::Disabled,        QPalette::Text, QColor(127, 127, 127));
   darkPalette.setColor(QPalette::Dark,            QColor(35, 35, 35));
   darkPalette.setColor(QPalette::Shadow,          QColor(20, 20, 20));
   darkPalette.setColor(QPalette::Button,          QColor(53, 53, 53));
   darkPalette.setColor(QPalette::ButtonText,      Qt::white);
   darkPalette.setColor(QPalette::Disabled,        QPalette::ButtonText, QColor(127, 127, 127));
   darkPalette.setColor(QPalette::BrightText,      Qt::red);
   darkPalette.setColor(QPalette::Link,            QColor(42, 130, 218));
   //darkPalette.setColor(QPalette::Highlight,       QColor(42, 130, 218));
   darkPalette.setColor(QPalette::Highlight,       QColor(42, 42, 42));
   darkPalette.setColor(QPalette::Disabled,        QPalette::Highlight, QColor(80, 80, 80));
   darkPalette.setColor(QPalette::HighlightedText, Qt::white);
   darkPalette.setColor(QPalette::Disabled,        QPalette::HighlightedText, QColor(127, 127, 127));
   a.setPalette(darkPalette);

   RigidBodySimulator w;
#if !defined(WIN32) && !defined(_WIN32) && !defined(__WIN32__) && !defined(__NT__)
   w.setFixedSize(430, 425);
#endif
   w.show();
   w.move(895, 180);

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   AllocConsole();
   freopen("CONOUT$", "w", stdout);
#endif

   // Initialize the window
   std::shared_ptr<Window> glfwWindow = std::make_shared<Window>("Simulation Viewer");

   if (!glfwWindow->initialize())
   {
      std::cout << "Error - Game::initialize - Failed to initialize the window" << "\n";
      return 1;
   }

   glfwMakeContextCurrent(NULL);

   Game game(&w, glfwWindow);
   game.start();

   w.raise();
   w.activateWindow();

   return a.exec();
}
