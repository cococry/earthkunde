#include <GL/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <leif/leif.h>
#include <GLFW/glfw3.h>

#define arrlen(arr) sizeof(arr) / sizeof(arr[0])

typedef enum {
  PageStart,
  PageAbout,
  PageReasonsForEndangoured,
  PageProtectiveMeasures,
  PageEnd
} page_t;

static uint32_t winw = 1080, winh = 1080;
static float margin = 15.0f;
static LfTexture backwardtex, shark1tex, shark2tex, whitesharktex, hammersharktex, whalesharktex, trashtex;
static LfFont titlefont, subtitlefont, smallfont;
static page_t currentpage;

static void btnbackward(page_t to);

void
resizecallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  lf_resize_display(width, height);
  winw = width;
  winh = height;
}

void centeredtext_x(const char* text, LfFont* font, LfUIElementProps props) {
  props.margin_left = 0.0f;
  lf_push_style_props(props);
  if(font)
    lf_push_font(font);
  lf_set_ptr_x_absolute((winw - lf_text_dimension(text).x) / 2.0f);
  lf_text(text);
  lf_pop_style_props();
  if(font)
    lf_pop_font();
}

void heading(const char* text) {
  LfUIElementProps props = lf_get_theme().text_props;
  props.margin_top = 20.0f;
  props.margin_bottom = 20.0f;
  lf_push_style_props(props);
  lf_push_font(&titlefont);
  lf_text(text);
  lf_pop_font();
  lf_pop_style_props();
}

void subheading(const char* text) {
  LfUIElementProps props = lf_get_theme().text_props;
  props.margin_top = 20.0f;
  props.margin_bottom = 15.0f;
  lf_push_style_props(props);
  lf_push_font(&subtitlefont);
  lf_text(text);
  lf_pop_font();
  lf_pop_style_props();
}

void paragraph(const char* text) {
  lf_push_font(&smallfont);
  lf_text(text);
  lf_pop_font();
}

void
pagestart() {
  // Title
  {
    LfUIElementProps props = lf_get_theme().text_props;
    props.margin_bottom = 10.0f;
    props.margin_top = 200.0f;
    centeredtext_x("Gefährdung von Haien", &titlefont, props);

    lf_next_line();

    centeredtext_x("Luca & Valentin 10c", NULL, lf_get_theme().text_props);
  }
  lf_next_line();
  // Image
  {
    LfUIElementProps props = lf_get_theme().image_props;
    props.margin_top = 30.0f;
    props.margin_left = 0.0f;
    props.corner_radius = 10.0f;
    uint32_t width = 800, height = 450;
    lf_set_ptr_x_absolute((winw - width) / 2.0f);
    lf_push_style_props(props);
    lf_image((LfTexture){.id = shark1tex.id, .width = width, .height = height});
    lf_pop_style_props();
  }

  lf_next_line();

  // Button
  {
    LfUIElementProps props = lf_get_theme().button_props;
    props.color = lf_color_from_hex(0x1ca7ec);
    props.corner_radius = 9.0f;
    props.border_width = 0.0f;
    props.margin_top = 30.0f;
    lf_push_style_props(props);
    float width = 180.0f;
    lf_set_ptr_x_absolute((winw - width) / 2.0f);
    if(lf_button_fixed("Mehr erfahren", width, -1) == LF_CLICKED) {
      currentpage = PageAbout;
    }
    lf_pop_style_props();
  }
}

void
pageabout() {
  heading("Haie: Jäger der Weltmeere");

  lf_next_line();
  
  paragraph("Haie gehören zu den faszinierendsten und zugleich am meisten gefürchteten Meeresbewohnern. Seit 400 Millionen Jahren schwimmen sie in unseren Ozeanen und haben sich im Laufe der Zeit zu perfekten Jägern entwickelt. Es gibt mittlerweile mehr als 500 Haiarten. Diese unterscheiden sich häufig stark voneinander. Sei es Größe, Lebensraum oder Verhalten. Hier erhälfst du einen Überblick über einige der bekanntesten und beeindruckendsten Haiarten.");

  lf_next_line();

  subheading("Der weiße Hai");

  lf_next_line();

  paragraph("Der Weiße Hai ist so ziehmlich der bekannteste Hai den es gibt. Er wird bis zu sechs Meter lang. Sein unverwechselbares Erscheinungsbild, ausgesttatet mit scharfenden, dreieckigen Zähnen ist wohl jedem bekannt. Weiße Haie sind meist in kälteren Küstengewässern zu finden. Sie sind bekannt als äußerst effiziente Jäger, die Robben, Seelöwen und gelegentlich sogar auch kleinere Wale jagen. Gegensätzlich zu ihrem Ruf greifen Weiße Haie selten Menschen. Die Art ist ebenfalls vom Aussterben bedroht.");

  lf_next_line();

  subheading("Der Hammerhai");

  lf_next_line();

  paragraph("Kommen wir zu einer weiteren bemerkenswerten Spezies, dem Hammerhai. Es gibt neun verschiedene Arten von Hammerhaie. Von diesen Arten ist der Große Hammerhai am bekanntesten. Charakteristisch für diese Haie ist ihre hammerförmige Kopfstruktur, die ihnen ein breites Sichtfeld und verbesserte elektrosensorische Fähigkeiten verleiht. Hammerhaie sind oft in tropischen Gewässern anzutreffen und jagen eine Vielzahl von Beutetieren. Zum Beispiel Fische, Rochen und Kalmare.");

  lf_next_line();

  subheading("Der Walhai");

  lf_next_line();

    paragraph("Der Walhai ist der größte Hai und ebenfalls der größte Fisch der Welt. Er kann mehr als 12 Meter lang werden und wiegt mehrere Tonnen. Obwhol dise Hai-Art so groß wird, sind sie sanfte Riesen, dis sich hauptsächlich von Plankton und kleinen Fischen ernähren. Walhaie sind in tropischen Ozeanen verbreitet und bekannt für ihre friedliche Natur. Sie sind auch bekannt für ihre sehr weitreichenden Wanderungen, die häufig tausende Kilometer weit gehen.");

  lf_next_line();

  // Image Galery
  {
    lf_set_no_render(true);
    LfUIElementProps props = lf_get_theme().image_props;
    props.corner_radius = 8.0f;
    props.margin_top = 20.0f;
    float width = 0.0f;
    float ptr_x_before = lf_get_ptr_x();
    uint32_t size = 250.0f;
    lf_push_style_props(props);
    lf_image((LfTexture){.id = whitesharktex.id, .width = size, .height = size});  
    lf_image((LfTexture){.id = hammersharktex.id, .width = size, .height = size}); 
    lf_image((LfTexture){.id = whalesharktex.id, .width = size, .height = size});
    lf_pop_style_props();
    width = lf_get_ptr_x() - ptr_x_before;
    lf_set_no_render(false);

    lf_set_ptr_x_absolute((winw - width) / 2.0f);
    lf_push_style_props(props);
    lf_image((LfTexture){.id = whitesharktex.id, .width = size, .height = size});  
    lf_image((LfTexture){.id = hammersharktex.id, .width = size, .height = size}); 
    lf_image((LfTexture){.id = whalesharktex.id, .width = size, .height = size});
    lf_pop_style_props();
  }
 
  lf_next_line();

  // Button
  {
    LfUIElementProps props = lf_get_theme().button_props;
    props.color = lf_color_from_hex(0x1ca7ec);
    props.corner_radius = 9.0f;
    props.border_width = 0.0f;
    props.margin_top = 30.0f;
    lf_push_style_props(props);
    float width = 320.0f;
    lf_set_ptr_x_absolute((winw - width) / 2.0f);
    if(lf_button_fixed("Zu den Gefährdungsursachen", width, -1) == LF_CLICKED) {
      currentpage = PageReasonsForEndangoured;
    }
    lf_pop_style_props();
  }

  btnbackward(PageStart);
}

void
pagereasonsforendangoured() {
  heading("Gefährdungsursachen von Haien");

  lf_next_line();

  paragraph("Haie sind seit Jahrmillionen ein fester Bestandteil der Ozeane. Sie sind ein wichtiger Bestandteil des Ökosystems der Meere. In den letzten Jahrzehnten sind jedoch viele Haiarten massiv bedroht. Diese Bedrohungen sind hauptsächlich menschlichen Ursprungs. Wir wrden nun die wichtigsten Faktoren, die zum Rückgang der Haipopulationen in unseren Weltmeeren beigetragen haben schildern.");

  lf_next_line();

  subheading("Überfischung und Beifang");

  lf_next_line();

  paragraph("Eine der größten Bedrohungen für Haie ist die Überfischung. Viele Haie werden gezielt gefangen, sei es wegen ihrer Flossen, ihres Fleisches oder ihrer Leber. Besonders die Nachfrage nach Haifischflossen für die Haifischflossensuppe, eine Delikatesse in einigen asiatischen Ländern, hat zu einem drastischen Rückgang der Haipopulationen geführt. Haie sind auch häufig Opfer des Beifangs, was bedeutet, dass sie unbeabsichtigt in Netzen und an Haken gefangen werden, die für andere Fischarten ausgelegt sind. Beifang stellt ein erhebliches Problem dar, da Haie oft schwer verletzt oder getötet werden, bevor sie ins Meer zurückgeworfen werden.");

  lf_next_line();

  subheading("Klimawandel");

  lf_next_line();

  paragraph("Der Klimawandel stellt eine zunehmende Bedrohung für Haie dar. Erhöhte Wassertemperaturen können die Verbreitung und das Verhalten von Haien verändern. Manche Arten sind temperaturabhängig und können gezwungen sein, in neue Gebiete zu migrieren, was ihre Fortpflanzung und ihr Überleben beeinträchtigen kann. Die Versauerung der Ozeane, eine Folge der erhöhten CO2-Konzentrationen in der Atmosphäre, wirkt sich negativ auf die marine Fauna und Flora aus, einschließlich der Beutetiere von Haien.");

  lf_next_line();

  subheading("Verschmutzung und Müll");

  lf_next_line();

  paragraph("Die Verschmutzung der Meere durch Plastik und andere Schadstoffe ist eine weitere ernsthafte Bedrohung für Haie. Plastikmüll wird oft von Haien verschluckt, was zu Verdauungsproblemen, Verletzungen und sogar zum Tod führen kann. Chemische Verschmutzung durch Pestizide, Schwermetalle und andere Giftstoffe kann sich ebenfalls negativ auf die Gesundheit der Haie auswirken und ihre Fortpflanzungsfähigkeit beeinträchtigen.");

  lf_next_line();

 {
    LfUIElementProps props = lf_get_theme().image_props;
    props.margin_top = 30.0f;
    props.margin_left = 0.0f;
    props.corner_radius = 10.0f;
    uint32_t width = 400, height = (400 * 9) / 16;
    lf_set_ptr_x_absolute((winw - width) / 2.0f);
    lf_push_style_props(props);
    lf_image((LfTexture){.id = trashtex.id, .width = width, .height = height});
    lf_pop_style_props();
  }

  lf_next_line();

  // Button
  {
    LfUIElementProps props = lf_get_theme().button_props;
    props.color = lf_color_from_hex(0x1ca7ec);
    props.corner_radius = 9.0f;
    props.border_width = 0.0f;
    props.margin_top = 30.0f;
    lf_push_style_props(props);
    float width = 320.0f;
    lf_set_ptr_x_absolute((winw - width) / 2.0f);
    if(lf_button_fixed("Weiter zu Schutzmaßnahmen", width, -1) == LF_CLICKED) {
      currentpage = PageProtectiveMeasures;
    }
    lf_pop_style_props();
  }


  btnbackward(PageAbout);
}

void
pageprotectivemeasures() {
  heading("Schutzmaßnahmen für Haie: Wege zur Erhaltung dieser faszinierenden Meeresbewohner");

  lf_next_line();

  paragraph("Haie sind essenzielle Bestandteile des marinen Ökosystems, doch viele ihrer Arten sind zunehmend bedroht. Um den Rückgang der Haipopulationen zu stoppen und ihre Zukunft zu sichern, sind umfassende und effektive Schutzmaßnahmen erforderlich. Dieser Artikel beleuchtet einige der wichtigsten Strategien und Initiativen zum Schutz der Haie weltweit.");

  lf_next_line();

  subheading("Internationale Abkommen und Gesetze");

  lf_next_line();

  paragraph("Internationale Abkommen spielen eine große Rolle beim Schutz der Haie. Das Washingtoner Artenschutzübereinkommen ist eines der wichtigsten Übereinkommen, das den internationalen Handel mit gefährdeten Tier- und Pflanzenarten eindemmt. Ebenfalls gibt es regionale Fischereiabkommen, wie die ICCAT, die Maßnahmen zum Schutz von Haien in ihren Fanggebieten .");

  lf_next_line();

  subheading("Schutzgebiete und Meeresschutzgebiete");

  lf_next_line();

  paragraph("Die Einrichtung von Meeresschutzgebieten  ist eine effektive Methode, um Haie und ihre Lebensräume zu schützen. Diese Gebiete bieten Schutz vor Überfischung, Verschmutzung und anderen menschlichen Aktivitäten. In Meeresschutzgebieten wie dem Great Barrier Reef Marine Park in Australien und den Galapagos-Inseln wurden signifikante Verbesserungen der Haipopulationen beobachtet. Meeresschutzgebiete bieten nicht nur Schutz für Haie, sondern sind auch gut für die Erholung der gesamten Biodiversität in unserem Weltmeeren.");

  lf_next_line();

  subheading("Fangquoten und Handelsbeschränkungen");

  lf_next_line();

  paragraph("Wissenschaftliche Forschung ist sehr wichtig, um fundierte Schutzmaßnahmen zu entwickeln. Forschungen über das Verhalten von Haien liefern wichtige Daten, die für die Verwaltung und den Schutz dieser Arten von großer Bedeutung sind. Technologien wie DNA-Analysen ermöglichen es Wissenschaftlern, die Wanderungen und die genetische Vielfalt von Haien zu verfolgen. Diese Informationen sind wichtif, um effektive Schutzstrategien zu entwickeln und die Auswirkungen von Schutzmaßnahmen zu bewerten.");

  lf_next_line();

  subheading("Öffentlichkeitsarbeit und Bildung");

  lf_next_line();

  paragraph("Öffentlichkeitsarbeit und Bildungsprogramme sind wichtig, um das Bewusstsein für den Schutz der Haie zu stärken. Viele Leute haben Angst vor Haien oder sehen sie als Bedrohung, ohne ihre ökologische Bedeutung zu verstehen. Initiativen wie Shark Week und Dokumentarfilme über Haie tragen dazu bei, die öffentliche Wahrnehmung zu ändern und die Bedeutung des Hai-Schutzes hervorzuheben. Bildungsprogramme in Schulen und Gemeinden können ebenfalls helfen, das Verständnis und die Unterstützung für Hai-Schutzmaßnahmen zu fördern.");

  lf_next_line();

  // Button
  {
    LfUIElementProps props = lf_get_theme().button_props;
    props.color = lf_color_from_hex(0x1ca7ec);
    props.corner_radius = 9.0f;
    props.border_width = 0.0f;
    props.margin_top = 30.0f;
    lf_push_style_props(props);
    float width = 250.0f;
    lf_set_ptr_x_absolute((winw - width) / 2.0f);
    if(lf_button_fixed("Weiter zum Ende", width, -1) == LF_CLICKED) {
      currentpage = PageEnd;
    }
    lf_pop_style_props();
  }

  lf_next_line();

  btnbackward(PageProtectiveMeasures);
}

void pageend() {
  // Title
  {
    LfUIElementProps props = lf_get_theme().text_props;
    props.margin_bottom = 10.0f;
    props.margin_top = 200.0f;
    centeredtext_x("Das wars, Vielen Dank", &subtitlefont, props);

    lf_next_line();

    centeredtext_x("Wir hoffen, du konntest etwas lernen und bedanken uns.", NULL, lf_get_theme().text_props);

    lf_next_line();

    centeredtext_x("Luca & Valentin 10c", NULL, lf_get_theme().text_props);
  }
  lf_next_line();
  // Image
  {
    LfUIElementProps props = lf_get_theme().image_props;
    props.margin_top = 30.0f;
    props.margin_left = 0.0f;
    props.corner_radius = 10.0f;
    uint32_t width = 800, height = 450;
    lf_set_ptr_x_absolute((winw - width) / 2.0f);
    lf_push_style_props(props);
    lf_image((LfTexture){.id = shark2tex.id, .width = width, .height = height});
    lf_pop_style_props();
  }

  lf_next_line();

  // Button
  {
    LfUIElementProps props = lf_get_theme().button_props;
    props.color = lf_color_from_hex(0x1ca7ec);
    props.corner_radius = 9.0f;
    props.border_width = 0.0f;
    props.margin_top = 30.0f;
    lf_push_style_props(props);
    float width = 220.0f;
    lf_set_ptr_x_absolute((winw - width) / 2.0f);
    if(lf_button_fixed("Rundgang beenden", width, -1) == LF_CLICKED) {
      exit(0);
    }
    lf_pop_style_props();
  }

}


typedef void (*page_func_t)(void);
static page_func_t pages[] = {
  pagestart,
  pageabout,
  pagereasonsforendangoured,
  pageprotectivemeasures,
  pageend
};


void
btnbackward(page_t to) {
  {
    float width = 20.0f, height = 40.0f;
    lf_set_ptr_x_absolute(margin);
    lf_set_ptr_y_absolute(winh - height - margin * 2.0f);
    lf_set_line_should_overflow(false);
    LfUIElementProps props = lf_get_theme().button_props;
    props.margin_left = 0;
    props.margin_right = 0;
    props.padding = 0;
    props.color = LF_NO_COLOR;
    props.border_width = 0;
    lf_push_style_props(props);
    if(lf_image_button(((LfTexture){.id = backwardtex.id, .width = width, .height = height})) == LF_CLICKED) {
      currentpage = to;
    }
    lf_set_line_should_overflow(true);
    lf_pop_style_props();
  }
}

int
main() {
  glfwInit();
  GLFWwindow* win = glfwCreateWindow(winw, winh, "Earthkunde", NULL, NULL);

  glfwMakeContextCurrent(win);

  glfwSetFramebufferSizeCallback(win, resizecallback);

  lf_init_glfw(winw, winh, win);
  LfTheme theme = lf_get_theme();
  theme.div_props.color = LF_NO_COLOR;
  theme.text_props.text_color = LF_BLACK;
  lf_set_theme(theme);

  titlefont = lf_load_font("./inter-bold.ttf", 60);
  subtitlefont = lf_load_font("./inter-bold.ttf", 40);
  smallfont = lf_load_font("./inter.ttf", 20);

  backwardtex = lf_load_texture("./backward.png", true, LF_TEX_FILTER_LINEAR);
  shark1tex = lf_load_texture("./shark1.jpg", true, LF_TEX_FILTER_LINEAR);
  shark2tex = lf_load_texture("./shark2.jpg", true, LF_TEX_FILTER_LINEAR);
  whitesharktex = lf_load_texture("./whiteshark.jpg", true, LF_TEX_FILTER_LINEAR);
  hammersharktex = lf_load_texture("./hammershark.jpg", true, LF_TEX_FILTER_LINEAR);
  whalesharktex = lf_load_texture("./whaleshark.jpg", true, LF_TEX_FILTER_LINEAR);
  trashtex = lf_load_texture("./trash.jpg", true, LF_TEX_FILTER_LINEAR);

  lf_set_text_wrap(true);
  while(!glfwWindowShouldClose(win)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0f);

    lf_begin();

    
    lf_div_begin(((vec2s){margin, margin}), ((vec2s){winw - (margin * 2.0f), winh - (margin * 2.0f)}), false);

    pages[currentpage]();

    lf_div_end();

    lf_end();


    glfwPollEvents();
    glfwSwapBuffers(win);
  }

  glfwDestroyWindow(win);
  glfwTerminate();
}
