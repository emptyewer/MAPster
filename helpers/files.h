#ifndef FILES_H
#define FILES_H
#include <QDir>
#include <QVector>
#include <QFileInfo>
#include <QStandardPaths>
#include <QCoreApplication>

#include "mystructs.h"
#include "xml/XMLDomDocument.h"

class files
{
public:
    files();
    QString get_genome_filename(genome g);
    QString get_genome_url(genome g);
    // Return Default Directory Names
    QString get_mapster_dir();
    QString get_mapster_genomes_dir();
    QString get_mapster_queues_dir();
    QString get_mapster_configs_dir();
    QVector<genome> get_genomes_list();
    void create_documents_folder();

private:
    void make_directory(QString path);
    QString documents_dir;
};

#endif // FILES_H
