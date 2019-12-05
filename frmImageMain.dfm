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
      BorderStyle = bsNone
      ButtonFlow = cbfVertical
      ButtonHeight = 30
      ButtonOptions = [boFullSize, boGradientFill, boShowCaptions, boBoldCaptions]
      Categories = <
        item
          Caption = 'Filtros'
          Color = 15400959
          Collapsed = True
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
            end
            item
              Action = actAnd
            end
            item
              Action = actOr
            end
            item
              Action = actXor
            end>
        end
        item
          Caption = 'Morfologia Matem'#225'tica'
          Color = 16777194
          Collapsed = True
          Items = <
            item
              Action = actDilation
            end
            item
              Action = actErosion
            end
            item
              Action = actOpening
            end
            item
              Action = actClosure
            end
            item
              Action = actInnerBorder
            end
            item
              Action = actExternalBorder
            end
            item
              Action = actGradient
            end
            item
              Action = actHitMiss
            end>
        end
        item
          Caption = 'Morfologia Escala de Cinza'
          Color = 16777194
          Collapsed = True
          Items = <
            item
              Action = actDilateGS
            end
            item
              Action = actErosionGS
            end
            item
              Action = actOpeningGS
            end
            item
              Action = actClosureGS
            end
            item
              Action = actGradientGS
            end
            item
              Action = actTopHat
            end
            item
              Action = actBottomHat
            end>
        end
        item
          Caption = 'Transforma'#231#245'es'
          Color = 15395839
          Collapsed = True
          Items = <
            item
              Action = actNegative
            end
            item
              Action = actDynamicRange
            end
            item
              Action = actLogTransf
            end
            item
              Action = actSigmoid
            end
            item
              Action = actLinearTransform
            end>
        end
        item
          Caption = 'Exerc'#237'cios'
          Color = 15395839
          Collapsed = True
          Items = <
            item
              Action = actArnoldsCatTransform
            end>
        end>
      RegularButtonColor = clWhite
      SelectedButtonColor = 15132390
      ShowHint = True
      TabOrder = 0
      ExplicitTop = 114
      ExplicitHeight = 522
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
    object actArnoldsCatTransform: TAction
      Category = 'Exerc'#237'cios'
      Caption = 'Transf. do Gato de Arnold'
      OnExecute = actArnoldsCatTransformExecute
    end
    object actDilation: TAction
      Category = 'Morfologia Matem'#225'tica'
      Caption = 'Dilata'#231#227'o'
      OnExecute = actDilationExecute
    end
    object actErosion: TAction
      Category = 'Morfologia Matem'#225'tica'
      Caption = 'Eros'#227'o'
      OnExecute = actErosionExecute
    end
    object actOpening: TAction
      Category = 'Morfologia Matem'#225'tica'
      Caption = 'Abertura'
      OnExecute = actOpeningExecute
    end
    object actClosure: TAction
      Category = 'Morfologia Matem'#225'tica'
      Caption = 'Fechamento'
      OnExecute = actClosureExecute
    end
    object actInnerBorder: TAction
      Category = 'Morfologia Matem'#225'tica'
      Caption = 'Borda Interna'
      OnExecute = actInnerBorderExecute
    end
    object actExternalBorder: TAction
      Category = 'Morfologia Matem'#225'tica'
      Caption = 'Borda Externa'
      OnExecute = actExternalBorderExecute
    end
    object actGradient: TAction
      Category = 'Morfologia Matem'#225'tica'
      Caption = 'Gradiente Morfol'#243'gico'
      OnExecute = actGradientExecute
    end
    object actNegative: TAction
      Category = 'Transforma'#231#245'es'
      Caption = 'Negativo'
      OnExecute = actNegativeExecute
    end
    object actDynamicRange: TAction
      Category = 'Transforma'#231#245'es'
      Caption = 'Transf. 8 tons de cinza'
      Hint = 'Transforma a imagem em 8 tons de cinza usando faixas din'#226'micas'
      OnExecute = actDynamicRangeExecute
    end
    object actLogTransf: TAction
      Category = 'Transforma'#231#245'es'
      Caption = 'Transforma'#231#227'o Logar'#237'timica'
      OnExecute = actLogTransfExecute
    end
    object actSigmoid: TAction
      Category = 'Transforma'#231#245'es'
      Caption = 'Transforma'#231#227'o Sigmoid'
      OnExecute = actSigmoidExecute
    end
    object actAnd: TAction
      Category = 'Filtros'
      Caption = 'And'
      OnExecute = actAndExecute
    end
    object actOr: TAction
      Category = 'Filtros'
      Caption = 'Or'
      OnExecute = actOrExecute
    end
    object actXor: TAction
      Category = 'Filtros'
      Caption = 'Xor'
      OnExecute = actXorExecute
    end
    object actDilateGS: TAction
      Category = 'Morfologia Escala de Cinza'
      Caption = 'Dilata'#231#227'o'
      OnExecute = actDilateGSExecute
    end
    object actErosionGS: TAction
      Category = 'Morfologia Escala de Cinza'
      Caption = 'Eros'#227'o'
      OnExecute = actErosionGSExecute
    end
    object actOpeningGS: TAction
      Category = 'Morfologia Escala de Cinza'
      Caption = 'Abertura'
      OnExecute = actOpeningGSExecute
    end
    object actClosureGS: TAction
      Category = 'Morfologia Escala de Cinza'
      Caption = 'Fechamento'
      OnExecute = actClosureGSExecute
    end
    object actGradientGS: TAction
      Category = 'Morfologia Escala de Cinza'
      Caption = 'Gradiente'
      OnExecute = actGradientGSExecute
    end
    object actHitMiss: TAction
      Category = 'Morfologia Matem'#225'tica'
      Caption = 'Hit or Miss'
      OnExecute = actHitMissExecute
    end
    object actTopHat: TAction
      Category = 'Morfologia Escala de Cinza'
      Caption = 'Top Hat'
      OnExecute = actTopHatExecute
    end
    object actBottomHat: TAction
      Category = 'Morfologia Escala de Cinza'
      Caption = 'Bottom Hat'
      OnExecute = actBottomHatExecute
    end
    object actLinearTransform: TAction
      Category = 'Transforma'#231#245'es'
      Caption = 'Transforma'#231#227'o Linear'
      OnExecute = actLinearTransformExecute
    end
  end
  object openDialog: TOpenDialog
    Left = 617
    Top = 32
  end
end
