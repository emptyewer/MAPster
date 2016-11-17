#include "files.h"

files::files()
{
    documents_dir = QStandardPaths::locate(QStandardPaths::DocumentsLocation,
                                           QString(), QStandardPaths::LocateDirectory);
}

QString files::get_genome_filename(genome g) {
    QString mapster_genomes_dir = get_mapster_genomes_dir();
    QFileInfo fileInfo(g.url.toString());
    QString gfn = QDir(mapster_genomes_dir).filePath(fileInfo.fileName());
    return gfn;
}

QString files::get_mapster_dir() {
    return QDir(documents_dir).filePath("MAPster Files");
}

QString files::get_mapster_genomes_dir() {
    QString mapster_dir = get_mapster_dir();
    return QDir(mapster_dir).filePath("Genomes");
}

QString files::get_mapster_queues_dir() {
    QString mapster_dir = get_mapster_dir();
    return QDir(mapster_dir).filePath("Queues");
}

QString files::get_mapster_configs_dir() {
    QString mapster_dir = get_mapster_dir();
    return QDir(mapster_dir).filePath("Configs");
}

QString files::get_genome_url(genome g) {
    return g.url.toString();
}

void files::make_directory(QString path)
{
    if (!QDir(path).exists())
    {
        QDir().mkpath(path);
    }
}

void files::create_documents_folder() {
    make_directory(get_mapster_dir());
    make_directory(get_mapster_configs_dir());
    make_directory(get_mapster_queues_dir());
    make_directory(get_mapster_genomes_dir());
}

QVector<genome> files::get_genomes_list() {
    QString appdir = QCoreApplication::applicationDirPath();
    QString appdir_configsdir = QDir(appdir).filePath("configs");
    QString xml_file = QDir(appdir_configsdir).filePath("genome_list.xml");
    std::string str = xml_file.toStdString();
    const char* p = str.c_str();
    QVector<genome> genomes_list;
    string value;
    XmlDomDocument* doc = new XmlDomDocument(p);
    if (doc) {
        for (int i = 0; i < doc->getChildCount("organisms", 0, "organism"); i++) {
            genome temp;

            temp.index = i;

            value = doc->getChildAttribute("organisms", 0, "organism", i, "species");
            temp.species = value.c_str();

            value = doc->getChildValue("organism", i, "name", 0 );
            temp.name = value.c_str();

            value = doc->getChildValue("organism", i, "type", 0 );
            temp.type = value.c_str();

            value = doc->getChildValue("organism", i, "url", 0 );
            QUrl _url(value.c_str());
            temp.url = _url;
            genomes_list.append(temp);
        }
        delete doc;
    }
    return genomes_list;
}
