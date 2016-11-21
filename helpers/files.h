#ifndef FILES_H
#define FILES_H
#include <QDir>
#include <QVector>
#include <QFileInfo>
#include <QStandardPaths>
#include <QCoreApplication>
#include <archive.h>
#include <archive_entry.h>

#include <helpers/includes.h>
#include "mystructs.h"
#include "xml/XMLDomDocument.h"

class files
{
public:
    files();
    QString get_genome_filepath(genome g);
    QString get_genome_filename(genome g);
    QString get_genome_url(genome g);
    // Return Default Directory Names
    QString get_mapster_dir();
    QString get_mapster_genomes_dir();
    QString get_mapster_queues_dir();
    QString get_mapster_configs_dir();
    QVector<genome> get_genomes_list();
    void create_documents_folder();
    void untar_files_mac(genome g);
    void extract(const char *filename);

private:
    void make_directory(QString path);
    QString documents_dir;
    int copy_data(struct archive *ar, struct archive *aw);
};

#endif // FILES_H
