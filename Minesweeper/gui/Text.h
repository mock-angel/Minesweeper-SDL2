
class Font
{
    bool dirty = false;
    bool m_bold = false;
    unsigned int m_size = 12;
public:
    TTF_Font* m_TTFfont = NULL;

    Font(){m_TTFfont = TTF_OpenFont("resources/Roboto-Regular.ttf", m_size);}
    void setBold(bool t_bold){m_bold = t_bold;}
    void setSize(bool t_size){m_size = t_size;}

    bool bold(){return m_bold;}

    TTF_Font* getTTFfont(){
        if (!dirty) return m_TTFfont;

        m_TTFfont = TTF_OpenFont("resources/Roboto-Regular.ttf", m_size);

        dirty = false;
        return m_TTFfont;
    };
};

///TODO: Test default font and declare one set as default;


class TextLine
{
    bool dirty = false;
    bool useDirty = false;  //false -> less memory consumption, more time to process surface
                            //true -> more memory consumption(1 surface memory), less time for surface blit.
    Str m_text = "";
    ///const Font * m_font = NULL;
    Font * m_bufferFont = NULL;
    Font * m_useNextFont = NULL;

    SDL_Surface * m_bufferSurface = NULL;
    ColorRGB m_color = {255, 255, 255};

public:
    void setText(Str t_text);
    Str text();

    Rect m_rect = {0, 0, 0, 0};

    void setFont(Font* t_font);
    void setBold(bool t_bold);
    void setSize(unsigned short t_size);

    Rect predicted_rect();


    void updateFont(Font* t_font);
    const Font* font();

    TextLine(){
        m_useNextFont = new Font();
    }
    TextLine(Str t_text);

    void draw(SDL_Surface * t_surface);
};

TextLine::TextLine(Str t_text){m_text = t_text;}

void TextLine::setBold(bool t_bold)
{
    m_bufferFont->setBold(t_bold);
    dirty = true;
}

void TextLine::setSize(unsigned short t_size)
{
    m_bufferFont->setSize(t_size);
    dirty = true;
}

void TextLine::setText(Str t_text)
{
    m_text = t_text;
    dirty = true;
}

Str TextLine::text()
{
    return m_text;
}

void TextLine::setFont(Font* t_font) // Use only during initialisation. Use updateFont method instead on normal operations.
{
    if (t_font == NULL) return; //Safeguard for program.

    //Font * tempFont = NULL;

    //tempFont = m_bufferFont;

    m_bufferFont = m_useNextFont = t_font;

    //delete tempFont;

    dirty = true;

}

void TextLine::updateFont(Font* t_font) // Simpler
{
    if (t_font == NULL) return; //Safeguard for program.

    m_useNextFont = t_font;

    dirty = true;
}

const Font* TextLine::font()
{
    return m_bufferFont;
}

void TextLine::draw(SDL_Surface * t_surface) // Normal draw function.
{

    if (dirty)
    {
        if (m_bufferFont != m_useNextFont) //Font object changed.
            m_bufferFont = m_useNextFont;

        m_bufferSurface = TTF_RenderText_Blended(m_bufferFont->getTTFfont(), m_text.c_str(), m_color.SDLColor);

        if (m_bufferSurface == NULL)
        {
            printf("%s\n", SDL_GetError());
        }
        //Get width and height of the created surface containing text.
        else{
            m_rect.w = m_bufferSurface->w;
            m_rect.h = m_bufferSurface->h;
            //printf(" THis is surf %d \n", m_rect.h);
        }
        //generateFont();
        //generateSurface(); //Place generate Surface code here.
        dirty = false;
    }

    ///m_bufferSurface = TTF_RenderText_Blended(m_font->m_TTFfont, m_text.c_str(), m_color.SDLColor);
    ///printf("%s\n", SDL_GetError());
    if (!useDirty)
    {
        Rect rect = m_rect;
        rect.x = 0;
        rect.y = 0;
        SDL_BlitSurface(m_bufferSurface, &rect, t_surface, &m_rect);
    }
}

Rect TextLine::predicted_rect() // Normal draw function.
{
    Rect prect;

    if (m_bufferFont != NULL) TTF_SizeText(m_bufferFont->getTTFfont(), m_text.c_str(), &prect.w, &prect.h);
    else TTF_SizeText(m_useNextFont->getTTFfont(), m_text.c_str(), &prect.w, &prect.h);

    return prect;
}


class TextWall
{
    std::vector<TextLine> textLines;

    std::vector<Str> _text_paragraph;
    bool m_dirty = true;

public:
    void setText(Str t_text);
    void setText(int t_lineIndex, Str t_text);
    void addLine(Str t_text);

    void draw(SDL_Surface * t_surface);
    //void parse_text();
    void _renderBuffer();
    void draw();
};


void TextWall::setText(Str t_text)
{
    //_text_paragraph = t_text;
    m_dirty = true;
}

void TextWall::setText(int t_lineIndex, Str t_text)
{
    _text_paragraph[t_lineIndex] = t_text;
    m_dirty = true;
}

void TextWall::addLine(Str t_text)
{
    _text_paragraph.push_back(t_text);
    TextLine hhh;
    hhh.setText(t_text);

    textLines.push_back(hhh);

    m_dirty = true;
}

void TextWall::draw(SDL_Surface * t_surface)
{
    if (m_dirty)
    {
        //Update each ones rect.
        int height = 0;//include offset.
        for(std::vector<TextLine>::iterator currentLine = textLines.begin(); currentLine  != textLines.end(); ++currentLine)
        {   ///Iterate through all TextLine objects.

            (*currentLine).m_rect.y = height;
            height += (*currentLine).predicted_rect().h;
            printf("%d  \n", height);
        }
        m_dirty = false;
    }

    for(std::vector<TextLine>::iterator currentLine = textLines.begin(); currentLine  != textLines.end(); ++currentLine)
    {
        ///Iterate through all TextLine objects.
        (*currentLine).draw(t_surface);
        printf("%d  \n", (*currentLine).m_rect.y);
    }

}
