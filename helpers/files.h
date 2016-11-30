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

class Files
{
public:
    Files();
    QString get_genome_filepath(Genome g);
    QString get_genome_filename(Genome g);
    QString get_genome_url(Genome g);
    // Return Default Directory Names
    QString get_mapster_dir();
    QString get_mapster_genomes_dir();
    QString get_mapster_queues_dir();
    QString get_mapster_configs_dir();
    QString get_mapster_output_dir();
    QVector<Genome> get_genomes_list();
    void create_documents_folder();
    void untar_files_mac(Genome g);
    void extract(const char *filename);
    void make_directory(QString path);
private:

    QString documents_dir;
    int copy_data(struct archive *ar, struct archive *aw);
};

#endif // FILES_H
