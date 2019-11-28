object formImageMain: TformImageMain
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Processamento de Imagens'
  ClientHeight = 489
  ClientWidth = 764
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  StyleElements = [seFont, seBorder]
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 185
    Top = 0
    Width = 579
    Height = 489
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitLeft = 192
    ExplicitTop = 80
    ExplicitWidth = 521
    ExplicitHeight = 297
    object hist1: TPanel
      Left = 17
      Top = 280
      Width = 264
      Height = 138
      Color = clGray
      ParentBackground = False
      TabOrder = 0
      StyleElements = [seFont, seBorder]
      object Panel2: TPanel
        AlignWithMargins = True
        Left = 4
        Top = 4
        Width = 256
        Height = 130
        Align = alClient
        BevelOuter = bvNone
        Color = clSilver
        ParentBackground = False
        TabOrder = 0
        StyleElements = [seFont, seBorder]
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 321
        ExplicitHeight = 137
      end
    end
    object Panel3: TPanel
      Left = 297
      Top = 280
      Width = 264
      Height = 138
      Color = clGray
      ParentBackground = False
      TabOrder = 1
      StyleElements = [seFont, seBorder]
      object Panel4: TPanel
        AlignWithMargins = True
        Left = 4
        Top = 4
        Width = 256
        Height = 130
        Align = alClient
        BevelOuter = bvNone
        Color = clSilver
        ParentBackground = False
        TabOrder = 0
        StyleElements = [seFont, seBorder]
      end
    end
  end
  object Panel5: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 489
    Align = alLeft
    TabOrder = 1
    object Button2: TButton
      Left = 56
      Top = 449
      Width = 75
      Height = 25
      Caption = 'Teste'
      TabOrder = 0
      OnClick = Button1Click
    end
  end
end
