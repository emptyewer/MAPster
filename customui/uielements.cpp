#include "uielements.h"

UIElements::UIElements() {}

parameters UIElements::get_parameters(MainWindow *parent) {
  parameters params;
  if (parent->ui->pairwise_on) {
    params.pairwise = true;
    int files_count1 = parent->ui->selected_files_list1->count();
    int files_count2 = parent->ui->selected_files_list1->count();
    for (int i = 0; i < files_count1; i++) {
      params.reads1 += parent->ui->selected_files_list1->item(i)->text();
    }
    for (int i = 0; i < files_count2; i++) {
      params.reads2 += parent->ui->selected_files_list2->item(i)->text();
    }
  } else {
    params.pairwise = false;
    int files_count1 = parent->ui->selected_files_list1->count();
    for (int i = 0; i < files_count1; i++) {
      params.reads1 += parent->ui->selected_files_list1->item(i)->text();
    }
  }
  params.output_filename = parent->ui->output_filename->text();
  params.threads = parent->ui->threads_sbox->value();
  params.genome = parent->genomes_list[parent->genome_index];
  return params;
}


void UIElements::pairwise_toggle(MainWindow *parent, int i) {
  if (i == 0) {
      parent->ui->selected_files_list2->setVisible(false);
      parent->ui->selected_files2_label->setVisible(false);
      parent->ui->selected_files1_label->setText("Unpaired Reads");
    }
  else {
      parent->ui->selected_files_list1->setVisible(true);
      parent->ui->selected_files_list2->setVisible(true);
      parent->ui->selected_files2_label->setVisible(true);
      parent->ui->selected_files1_label->setText("Paired Reads (Set 1)");
      parent->ui->selected_files2_label->setText("Paired Reads (Set 2)");
    }
}
