object formImageMain: TformImageMain
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Processamento de Imagens'
  ClientHeight = 640
  ClientWidth = 742
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
    Width = 557
    Height = 640
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object Panel2: TPanel
      Left = 0
      Top = 494
      Width = 557
      Height = 146
      Align = alBottom
      BevelOuter = bvNone
      Padding.Left = 10
      Padding.Top = 4
      Padding.Right = 10
      Padding.Bottom = 4
      TabOrder = 0
      object hist1: TPanel
        Left = 10
        Top = 4
        Width = 264
        Height = 138
        Align = alLeft
        Color = clGray
        ParentBackground = False
        TabOrder = 0
        StyleElements = [seFont, seBorder]
        object originalHistCanvas: TPanel
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
      object Panel3: TPanel
        Left = 283
        Top = 4
        Width = 264
        Height = 138
        Align = alRight
        Color = clGray
        ParentBackground = False
        TabOrder = 1
        StyleElements = [seFont, seBorder]
        object transformHistCanvas: TPanel
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
    object pnlImages: TPanel
      AlignWithMargins = True
      Left = 3
      Top = 3
      Width = 551
      Height = 276
      Align = alTop
      BevelOuter = bvNone
      Color = clWhite
      Padding.Left = 2
      Padding.Right = 2
      ParentBackground = False
      TabOrder = 1
      StyleElements = [seFont, seBorder]
      object transformImgCanvas: TPanel
        AlignWithMargins = True
        Left = 283
        Top = 10
        Width = 256
        Height = 256
        Cursor = crCross
        Margins.Left = 10
        Margins.Top = 10
        Margins.Right = 10
        Margins.Bottom = 10
        Align = alRight
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        StyleElements = [seFont, seBorder]
        OnClick = originalImgCanvasClick
        OnMouseEnter = originalImgCanvasMouseEnter
        OnMouseMove = originalImgCanvasMouseMove
      end
      object originalImgCanvas: TPanel
        AlignWithMargins = True
        Left = 12
        Top = 10
        Width = 256
        Height = 256
        Cursor = crCross
        Margins.Left = 10
        Margins.Top = 10
        Margins.Right = 10
        Margins.Bottom = 10
        Align = alLeft
        BevelOuter = bvNone
        Color = clWhite
        DragCursor = crCross
        ParentBackground = False
        TabOrder = 1
        StyleElements = [seFont, seBorder]
        OnClick = originalImgCanvasClick
        OnMouseEnter = originalImgCanvasMouseEnter
        OnMouseMove = originalImgCanvasMouseMove
        ExplicitLeft = 10
        ExplicitTop = 13
      end
    end
    object Panel4: TPanel
      AlignWithMargins = True
      Left = 3
      Top = 285
      Width = 551
      Height = 206
      Align = alClient
      BevelKind = bkFlat
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 2
      StyleElements = [seFont, seBorder]
      object gridImage2: TStringGrid
        AlignWithMargins = True
        Left = 278
        Top = 3
        Width = 266
        Height = 196
        Align = alRight
        ColCount = 9
        DefaultColWidth = 28
        DefaultRowHeight = 20
        FixedCols = 0
        RowCount = 9
        FixedRows = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected]
        ScrollBars = ssNone
        TabOrder = 0
      end
      object gridImage1: TStringGrid
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 266
        Height = 196
        Align = alLeft
        ColCount = 9
        DefaultColWidth = 28
        DefaultRowHeight = 20
        FixedCols = 0
        RowCount = 9
        FixedRows = 0
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected]
        ScrollBars = ssNone
        TabOrder = 1
      end
    end
  end
  object Panel5: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 640
    Align = alLeft
    TabOrder = 1
    object CategoryButtons1: TCategoryButtons
      AlignWithMargins = True
      Left = 4
      Top = 87
      Width = 177
      Height = 549
      Align = alClient
      ButtonFlow = cbfVertical
      ButtonOptions = [boFullSize, boGradientFill, boShowCaptions, boVerticalCategoryCaptions]
      Categories = <
        item
          Caption = 'Filtros'
          Color = 15400959
          Collapsed = False
          Items = <
            item
              Action = actHistEqualize
            end
            item
              Action = actMeanFilter
            end
            item
              Action = actMedianFilter
            end
            item
              Action = actHighPassFilter
            end
            item
              Action = actRobertsFilter
            end
            item
              Action = actRobertsCrossedFilter
            end
            item
              Action = actHighBoost
            end
            item
              Action = actPrewitt
            end
            item
              Action = actSobelFilter
            end>
        end
        item
          Caption = 'Filtros Morfologia'
          Color = 16777194
          Collapsed = False
          Items = <
            item
            end
            item
            end
            item
            end
            item
            end
            item
            end
            item
            end
            item
            end
            item
            end
            item
            end
            item
            end>
        end>
      RegularButtonColor = clWhite
      SelectedButtonColor = 15132390
      TabOrder = 0
      ExplicitLeft = 1
      ExplicitTop = 1
      ExplicitWidth = 183
      ExplicitHeight = 638
    end
    object rdgElemento: TRadioGroup
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 177
      Height = 77
      Align = alTop
      Caption = 'Elemento Estruturante '
      Columns = 2
      TabOrder = 1
    end
  end
  object acttions: TActionManager
    Left = 689
    Top = 32
    StyleName = 'Platform Default'
    object actHistEqualize: TAction
      Category = 'Filtros'
      Caption = 'Equaliza'#231#227'o de Histograma'
      OnExecute = actHistEqualizeExecute
    end
    object actHighBoost: TAction
      Category = 'Filtros'
      Caption = 'Filtro High Boost'
      OnExecute = actHighBoostExecute
    end
    object actMeanFilter: TAction
      Category = 'Filtros'
      Caption = 'Filtro da M'#233'dia'
      OnExecute = actMeanFilterExecute
    end
    object actMedianFilter: TAction
      Category = 'Filtros'
      Caption = 'Filtro da Mediana'
      OnExecute = actMedianFilterExecute
    end
    object actHighPassFilter: TAction
      Category = 'Filtros'
      Caption = 'Filtro Passa Alta'
      OnExecute = actHighPassFilterExecute
    end
    object actRobertsFilter: TAction
      Category = 'Filtros'
      Caption = 'Filtro de Roberts'
      OnExecute = actRobertsFilterExecute
    end
    object actRobertsCrossedFilter: TAction
      Category = 'Filtros'
      Caption = 'Filtro de Roberts Cruzado'
      OnExecute = actRobertsCrossedFilterExecute
    end
    object actPrewitt: TAction
      Category = 'Filtros'
      Caption = 'Filtro de Prewitt'
      OnExecute = actPrewittExecute
    end
    object actSobelFilter: TAction
      Category = 'Filtros'
      Caption = 'Filtro de Sobel'
      OnExecute = actSobelFilterExecute
    end
  end
  object openDialog: TOpenDialog
    Left = 617
    Top = 32
  end
end
