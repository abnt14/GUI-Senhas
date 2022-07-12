#include <gtk/gtk.h>
#include <string.h>

//Definição variáveis globais
GtkApplication *app;
GtkBuilder *builder;
GtkTextBuffer *bufferSenha;
GtkTextBuffer *bufferDefinicaoSenha;
GtkTextIter start,end;
GtkWidget *dicaDefinicaoSenha;
GtkWidget *dicaInsercaoSenha;
GObject *inserirTexto;
GObject *inserirDefinicaoSenha;
GObject *janela;
GObject *botoes[10];
GObject *status;
GObject *botaoEnviar;
GObject *botaoDefinicaoSenha;
GObject *botaoApagar;
int valor;
int numBotao;
int contador;
char codigo01[100];
char codigo02[100];
gchar *codigoInserido;
gchar *senhaDefinida;
const char* textoStatus;

void funcaoBotaoApagar(){
	for(int n = 0; n <= 100; n++){
		if(codigo01[n] == 0){
			n--;

			codigo01[n] = 0;
			break;
		}
	}
	gtk_text_buffer_set_text(bufferSenha, codigo01,-1);
}

void configuraToolTips(){
	gtk_widget_set_tooltip_text(GTK_WIDGET(inserirDefinicaoSenha),"Digite uma senha que deseja usar");
	gtk_widget_set_tooltip_text(GTK_WIDGET(inserirTexto),"Digite a senha que você criou");
}

void configuraView(){
	inserirTexto = gtk_builder_get_object(builder,	"isrTexto");
	bufferSenha = gtk_text_view_get_buffer (GTK_TEXT_VIEW (inserirTexto));
}

void limpaTextView(){
	valor = 0;
	for(int d =0; d <=100;d++){
		codigo01[d] = 0;
		codigo02[d] = 0;
	}
	gtk_text_buffer_set_text(bufferSenha, "",-1);
}

void atualizaTextView(){
	if(contador ==0){
		sprintf(codigo01, "%d", valor);
		gtk_text_buffer_set_text(bufferSenha, codigo01, -1);
		contador++;
	}

	else{
		sprintf(codigo02, "%d", valor);
		strcat(codigo01,codigo02);
		gtk_text_buffer_set_text(bufferSenha, codigo01, -1);
	}
}

void verificaSenha(){
	gtk_text_buffer_get_bounds (bufferSenha, &start, &end);
	codigoInserido = gtk_text_buffer_get_text(bufferSenha, &start,&end,FALSE);

	if(senhaDefinida != 0){
		if(strcmp(codigoInserido,senhaDefinida) == 0){
			gtk_label_set_text(GTK_LABEL(status), "Status: Senha correta!");
			limpaTextView();
		}

		else{
			gtk_label_set_text(GTK_LABEL(status), "Status: Senha incorreta");
			limpaTextView();
		}
	}
}

void configuraViewDefinicaoSenha(){
	inserirDefinicaoSenha = gtk_builder_get_object(builder, "isrDefinicaoSenha");
	bufferDefinicaoSenha = gtk_text_view_get_buffer(GTK_TEXT_VIEW(inserirDefinicaoSenha));
}

void funcaoBotoes(){
	textoStatus = gtk_label_get_text(GTK_LABEL(status));

	for(int i=0; i<=9;i++){
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(botoes[i]))){
			valor = i;
			numBotao = i;
			atualizaTextView();
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(botoes[i]), false);
			}
		}
}

void ativaBotoes(){
	botoes[0] = gtk_builder_get_object(builder, "num0");
	botoes[1] = gtk_builder_get_object(builder, "num1");
	botoes[2] = gtk_builder_get_object(builder, "num2");
	botoes[3] = gtk_builder_get_object(builder, "num3");
	botoes[4] = gtk_builder_get_object(builder, "num4");
	botoes[5] = gtk_builder_get_object(builder, "num5");
	botoes[6] = gtk_builder_get_object(builder, "num6");
	botoes[7] = gtk_builder_get_object(builder, "num7");
	botoes[8] = gtk_builder_get_object(builder, "num8");
	botoes[9] = gtk_builder_get_object(builder, "num9");

	g_signal_connect(botoes[0], "toggled", G_CALLBACK(funcaoBotoes), NULL);
	g_signal_connect(botoes[1], "toggled", G_CALLBACK(funcaoBotoes), NULL);
	g_signal_connect(botoes[2], "toggled", G_CALLBACK(funcaoBotoes), NULL);
	g_signal_connect(botoes[3], "toggled", G_CALLBACK(funcaoBotoes), NULL);
	g_signal_connect(botoes[4], "toggled", G_CALLBACK(funcaoBotoes), NULL);
	g_signal_connect(botoes[5], "toggled", G_CALLBACK(funcaoBotoes), NULL);
	g_signal_connect(botoes[6], "toggled", G_CALLBACK(funcaoBotoes), NULL);
	g_signal_connect(botoes[7], "toggled", G_CALLBACK(funcaoBotoes), NULL);
	g_signal_connect(botoes[8], "toggled", G_CALLBACK(funcaoBotoes), NULL);
	g_signal_connect(botoes[9], "toggled", G_CALLBACK(funcaoBotoes), NULL);
}

void defineSenha(){
	gtk_text_buffer_get_bounds(bufferDefinicaoSenha, &start,&end);
	senhaDefinida = gtk_text_buffer_get_text(bufferDefinicaoSenha, &start,&end,FALSE);
}

void funcaoBotaoDefinicaoSenha(){
	defineSenha();
}

void ativaUI(){
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "test09.ui", NULL);
}

void iniciaWidgetsNecessarios(){
	botaoEnviar = gtk_builder_get_object(builder,"botaoEnviar");
	g_signal_connect(botaoEnviar, "clicked", G_CALLBACK(verificaSenha), NULL);
	status = gtk_builder_get_object(builder,"status");

	configuraViewDefinicaoSenha();

	botaoDefinicaoSenha = gtk_builder_get_object(builder, "botaoDefinicaoSenha");
	g_signal_connect(botaoDefinicaoSenha, "clicked", G_CALLBACK(funcaoBotaoDefinicaoSenha), NULL);

	botaoApagar = gtk_builder_get_object(builder, "botaoApagar");
	g_signal_connect(botaoApagar, "clicked", G_CALLBACK(funcaoBotaoApagar), NULL);
}

void criaJanela(){
	ativaUI();
	configuraView();
	ativaBotoes();
	iniciaWidgetsNecessarios();
	configuraToolTips();

	janela = gtk_builder_get_object(builder, "janela");
	gtk_window_set_application(GTK_WINDOW(janela), app);

	gtk_widget_show(GTK_WIDGET(janela));

	g_object_unref(builder);
}

int main(int argc,char *argv[]){
	int status;
	app = gtk_application_new("test09.desktop", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(criaJanela), NULL);

	status = g_application_run(G_APPLICATION(app), argc,argv);
	g_object_unref(app);

	return status;
}
