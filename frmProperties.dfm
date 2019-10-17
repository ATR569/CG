object formProperties: TformProperties
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Propriedades do objeto'
  ClientHeight = 463
  ClientWidth = 465
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 413
    Width = 465
    Height = 50
    Align = alBottom
    Padding.Left = 10
    Padding.Top = 10
    Padding.Right = 10
    Padding.Bottom = 10
    TabOrder = 0
    ExplicitTop = 285
    ExplicitWidth = 268
    object btnCancel: TButton
      Left = 11
      Top = 11
      Width = 112
      Height = 28
      Align = alLeft
      Cancel = True
      Caption = 'Cancelar'
      ModalResult = 2
      TabOrder = 0
    end
    object btnOk: TButton
      Left = 342
      Top = 11
      Width = 112
      Height = 28
      Align = alRight
      Caption = 'Ok'
      Default = True
      ModalResult = 1
      TabOrder = 1
      ExplicitLeft = 145
    end
  end
end
