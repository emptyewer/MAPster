#include "files.h"

Files::Files() {
  documents_dir =
      QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString(),
                             QStandardPaths::LocateDirectory);
}

QString Files::get_genome_filepath(Genome g) {
  QString mapster_genomes_dir = get_mapster_genomes_dir();
  QString gfn = QDir(mapster_genomes_dir).filePath(get_genome_filename(g));
  return gfn;
}

QString Files::get_genome_filename(Genome g) {
  QFileInfo fileInfo(g.url.toString());
  return fileInfo.fileName();
}

QString Files::get_mapster_dir() {
  return QDir(documents_dir).filePath("MAPsterFiles");
}

QString Files::get_mapster_genomes_dir() {
  QString mapster_dir = get_mapster_dir();
  return QDir(mapster_dir).filePath("Genomes");
}

QString Files::get_mapster_queues_dir() {
  QString mapster_dir = get_mapster_dir();
  return QDir(mapster_dir).filePath("Queues");
}

QString Files::get_mapster_configs_dir() {
  QString mapster_dir = get_mapster_dir();
  return QDir(mapster_dir).filePath("Configs");
}

QString Files::get_mapster_output_dir() {
  QString mapster_dir = get_mapster_dir();
  return QDir(mapster_dir).filePath("Output");
}

QString Files::get_genome_url(Genome g) { return g.url.toString(); }

void Files::make_directory(QString path) {
  if (!QDir(path).exists()) {
    QDir().mkpath(path);
  }
}

void Files::create_documents_folder() {
  make_directory(get_mapster_dir());
  make_directory(get_mapster_configs_dir());
  make_directory(get_mapster_queues_dir());
  make_directory(get_mapster_genomes_dir());
  make_directory(get_mapster_output_dir());
}

void Files::untar_files_mac(Genome g) {
  QString command = "tar xvfz \"" + get_genome_filepath(g) +"\" -C \"" + get_mapster_genomes_dir() + "\"" ;
  string command_str = command.toStdString();
  system(command_str.c_str());
}

void Files::extract(const char *filename) {
  struct archive *a = NULL;
  struct archive_entry *entry = NULL;
  int r;
  QString path_qstring = get_mapster_genomes_dir();
  string s = path_qstring.toStdString();

  a = archive_read_new();
  archive_read_support_filter_all(a);
  archive_read_support_format_all(a);
  archive_entry_set_pathname(entry, s.c_str());

  qDebug() << *filename;
  r = archive_read_open_filename(a, filename, 10240); // Note 1
  if (r != ARCHIVE_OK)
    exit(1);
  while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
    printf("%s\\n",archive_entry_pathname(entry));
    archive_read_data_skip(a);  // Note 2
  }
  r = archive_read_free(a);  // Note 3
}

QVector<Genome> Files::get_genomes_list() {
  QString appdir = QCoreApplication::applicationDirPath();
  QString appdir_configsdir = QDir(appdir).filePath("configs");
  QString xml_file = QDir(appdir_configsdir).filePath("genome_list.xml");
  std::string str = xml_file.toStdString();
  const char *p = str.c_str();
  QVector<Genome> genomes_list;
  string value;
  XmlDomDocument *doc = new XmlDomDocument(p);
  if (doc) {
    for (int i = 0; i < doc->getChildCount("organisms", 0, "organism"); i++) {
      Genome temp;
      temp.index = i;

      value = doc->getChildAttribute("organisms", 0, "organism", i, "species");
      temp.species = value.c_str();

      value = doc->getChildValue("organism", i, "name", 0);
      temp.name = value.c_str();

      value = doc->getChildValue("organism", i, "type", 0);
      temp.type = value.c_str();

      value = doc->getChildValue("organism", i, "url", 0);
      QUrl _url(value.c_str());
      temp.url = _url;

      value = doc->getChildValue("organism", i, "internalname", 0);
      temp.internal_name = value.c_str();

      genomes_list.append(temp);
    }
    delete doc;
  }
  return genomes_list;
}
