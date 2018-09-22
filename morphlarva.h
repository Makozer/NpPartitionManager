/* Beschreibung:
 * Die Klasse MorphLarva ist vom Namen her an die Larva von den Zergs in StarCraft 2 angelehnt.
 * http://starcraft.wikia.com/wiki/Larva
 *
 * Sie kann, wie ihr Vorbild, sich in unterschiedliche Funktionen "morphen", zudem ist sie auch das InterFace für das GUI
 * Als sogenannter Overseer stellt sie die Verbindung von der GUI zur Logik dar, über sie kann man im GUI alle Funktionen nutzen und aufrufen.
 * Als "Arbeiterklasse" heißt sie "worker" und führt Suchalgorithmen aus
 *
 * Dieser "etwas" unkonventionelle Aufbau ist die Lösung wie man die Kommunikation zwischen Klassen realisiert ohne auf Probleme wie
 * das Problem der "Circular dependency" zu stoßen
 * Für weitere Beschreibungen siehe Kommentare.
 * Zuständigkeit: Martin
 */
#ifndef MORPHLARVA_H
#define MORPHLARVA_H
#include <QVector>
#include <QString>
#include <vectorstash.h>
#include <liststash.h>
#include <memento.h>
#include <QObject>

// Qt Threading
#include <QMutex>
#include <QSize>
#include <QWaitCondition>
#include <QDebug>
#include <QThread>
#include <QApplication>
#include <QtConcurrent/QtConcurrent>

class MorphLarva : public QThread {
    Q_OBJECT
    // Die MorphLarva kann verschiedene Signale der GUI übermitteln
signals:
    void foundSolution();                        // signalisiert, dass das Ergebnis gefunden wurde.
    void noSolution();                           // signalisiert, dass kein Ergebnis möglich ist.
    void message(QString message);               // teilt mit, dass aufgrund bestimmter Ereignisse abgebrochen wurde.
public:
    MorphLarva();
    MorphLarva(const MorphLarva &copyLarva);     // Deep Copy Konstruktor
    ~MorphLarva();                               // Destruktor

    // Das wichtigste für die GUI ;)
    bool runCalc();                              // startet den Suchvorgang
    void setRootStash(VectorStash* stash);
    VectorStash *getSolutionStash();             // übergibt die Lösung
    Memento *getTimer();

    // Unwichtig für GUI, trotzdem zwingend public sichtbar
    void setSolutionStash(VectorStash* stash);   // setzt die Lösung
    void setNoSolution();                        // meldet, dass keine Lösung möglich ist
    void setMessage(QString msg);                // übergibt Signal an GUI
    void setOverseer(MorphLarva* overseer);      // setzt die Klasse als Overseer, die alle anderen überwacht
    MorphLarva* getOverseer();

    void setSuccess(bool success);
    bool hasSuccess();
    void setStrategy(quint8 strategy);           // legt die Strategie der suchenden Klasse fest
    quint8 getStrategy();
    void setGoal(quint32 goal);                  // setzt das Ziel
    quint32 getGoal();

    void search();                               // startet im jeweiligen Sucher den Vorgang, dass nach dem festgelegten Algorithmus gesucht wird

private:
    // Threading
    QVector<MorphLarva*> workers;                // Vector in dem der Overseer speichert, welche Arbeiterklassen er überwacht
    QVector<QFuture<void>> qfs;                  // Vector in dem der Overseer speichert, wieviele Threads offen sind
    QMutex mutex;                                // Mutex um Multithreadingprobleme zu beseitigen

    // Analyse & cleanup / readycheck / stop
    bool stopCalc();                             // stoppt sämtliche Threads
    bool cleanup();                              // räumt die Klasse auf, um erneut starten zu können
    bool readycheck();                           // prüft, ob die Klasse startbereit ist
    bool analysis();                             // Analyse der Ursprungsmenge, ob Berechnung sinnvoll

    // temporär
    void debug();    

    // SuchFunktionen
    void searchChaosRandom();                    // Suchalgorithmus der rein mit dem Zufall sucht, sehr unperformant.
    void searchOrderSort();                      // Intelligenter Suchalgorithmus der erkennt, wieviel noch fehlen würde zum Ergebnis und dieses dann sucht bzw generiert
    void searchDanceJinJang();                   // Schneller performanter Suchalgorithmus der zwei gleichgroße Mengen bildet und solange Coins hin und her schmeißt, bis die Lösung da ist
    void searchDanceS();                         // To Do :D
    static const quint8 fMax = 16;               // Legt fest, wie weit maximal bei der Fakultätssuche gesucht werden soll. Siehe Textdatei facultyresearch.txt
    void searchFaculty();                        // Geht JEDE MÖGLICHE Kombination durch ob eine Lösung möglich ist, allerdings mit Begrenzung
    void searchFaculty(quint8 pos, QVector<quint8> *picked);
    void searchPseudoPoly();                     // To Do :D

    // CheatCoin
    // Falls die ursprüngliche Menge nicht glatt durch 2 Teilbar ist wird ein "CheatCoin" hinzugefügt welcher dies ermöglicht, nachdem die Algorithmen durchgelaufen sind wird er wieder entfernt
    bool cheatCoin;                              // Speichert ob der Overseer "schummeln" musste :)
    bool addCheatCoin();                         // Hinzufügen vom CheatCoin
    bool removeCheatCoin();                      // Entfernen vom CheatCoin

    // Verschiedene Objekte
    MorphLarva* overseer;                        // Die Instanz speicher hier ihre ihr vorgesetzte Instanz, genannt Overseer

    VectorStash* rootStash;                      // Die ursprüngliche Menge von der ausgegangen wird
    VectorStash* memoryStash;                    // Der "Arbeitsspeicher" der jeweiligen Arbeiterklasse
    VectorStash* solutionStash;                  // Falls gesetzt: die Lösungsmenge

    RNGesus* rng;
    Memento* timer;


    bool success;                                // bool ob die Lösung gefunden wurde
    quint32 goal;                                // Der insgesamte Wert der gesuchten Teilmenge
    quint8 strategy;                             // Die Strategie der Arbeiterklasse

};

#endif // MORPHLARVA_H
